#pragma once

#include "interface.hh"
#include <cstdint>

#ifdef HAL_TIM_MODULE_ENABLED

namespace hal {

namespace pwm {
    constexpr inline uint32_t channel1 = 0x00000000U;
    constexpr inline uint32_t channel2 = 0x00000004U;
    constexpr inline uint32_t channel3 = 0x00000008U;
    constexpr inline uint32_t channel4 = 0x0000000CU;
    constexpr inline uint32_t channel5 = 0x00000010U;
    constexpr inline uint32_t channel6 = 0x00000014U;

    template <size_t index> constexpr inline uint32_t get_channel_from_index() {
        return (index - 1) << 2;
    }
    template <uint32_t channel> constexpr inline size_t get_index_from_channel() {
        return (channel >> 2) + 1;
    }

    template <typename PWM>
    concept PwmConcept = requires { typename PWM::pwm_token; };
}

template <TIM_HandleTypeDef* _handle, uint32_t _channel> class PWM {
public:
    template <Mode mode> static inline void start(uint32_t* buffer = nullptr, uint16_t length = 0) {
        if (mode == Mode::Normal) HAL_TIM_PWM_Start(_handle, _channel);
        else if (mode == Mode::It)
            HAL_TIM_PWM_Start_IT(_handle, _channel);
        else if (mode == Mode::Dma)
            HAL_TIM_PWM_Start_DMA(_handle, _channel, buffer, length);
    }

    static inline void set_pwm(uint32_t pwm) { compare_register() = pwm; }

    static inline void set_ratio(float ratio) { set_pwm(ratio * (_handle->Init.Period)); }

    static inline uint32_t period() { return _handle->Init.Period; }

    struct pwm_token { };

private:
    // capture/compare register
    static inline constexpr volatile uint32_t& compare_register() {
        auto address = &_handle->Instance->CCR1;
        return *(address + pwm::get_index_from_channel<_channel>() - 1);
    }
};

}

#endif