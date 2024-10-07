#pragma once

#include "interface.hh"

#ifdef HAL_TIM_MODULE_ENABLED

namespace hal {

enum class Mode {
    N,
    D,
    I
};

namespace pwm {
    constexpr inline uint32_t channel1 = 0x00000000U;
    constexpr inline uint32_t channel2 = 0x00000004U;
    constexpr inline uint32_t channel3 = 0x00000008U;
    constexpr inline uint32_t channel4 = 0x0000000CU;
    constexpr inline uint32_t channel5 = 0x00000010U;
    constexpr inline uint32_t channel6 = 0x00000014U;

    constexpr inline auto normal = Mode::N;
    constexpr inline auto dma = Mode::D;
    constexpr inline auto interrupt = Mode::I;

    template <typename PWM>
    concept pwm_concept = requires { typename PWM::pwm_token; };
}

template <TIM_HandleTypeDef* _handle, uint32_t _channel>
class PWM {
public:
    template <Mode mode>
    static inline void start(const uint32_t* buffer = nullptr, uint16_t length = 0) {
        if (mode == Mode::N)
            HAL_TIM_PWM_Start(_handle, _channel);
        else if (mode == Mode::I)
            HAL_TIM_PWM_Start_IT(_handle, _channel);
        else if (mode == Mode::D)
            HAL_TIM_PWM_Start_DMA(_handle, _channel, buffer, length);
    }

    static inline void set_pwm(uint32_t pwm) {
        compare_register() = pwm;
    }

    static inline void set_ratio(float ratio) {
        set_pwm(ratio * (_handle->Init.Period));
    }

    static inline uint32_t period() {
        return _handle->Init.Period;
    }

    struct pwm_token { };

private:
    // capture/compare register
    static inline constexpr volatile uint32_t& compare_register() {
        switch (_channel) {
        case pwm::channel1:
            return _handle->Instance->CCR1;
        case pwm::channel2:
            return _handle->Instance->CCR2;
        case pwm::channel3:
            return _handle->Instance->CCR3;
        case pwm::channel4:
            return _handle->Instance->CCR4;
        case pwm::channel5:
            return _handle->Instance->CCR5;
        case pwm::channel6:
            return _handle->Instance->CCR6;
        }
    }
};

}

#endif