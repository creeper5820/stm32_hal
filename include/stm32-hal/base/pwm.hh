#pragma once

#include <cstdint>

namespace hal {

namespace pwm {
    constexpr inline uint32_t channel1 = 0x00000000U;
    constexpr inline uint32_t channel2 = 0x00000004U;
    constexpr inline uint32_t channel3 = 0x00000008U;
    constexpr inline uint32_t channel4 = 0x0000000CU;
    constexpr inline uint32_t channel5 = 0x00000010U;
    constexpr inline uint32_t channel6 = 0x00000014U;

    template <std::size_t index> constexpr inline uint32_t get_channel_from_index() {
        return (index - 1) << 2;
    }
    template <uint32_t channel> constexpr inline std::size_t get_index_from_channel() {
        return (channel >> 2) + 1;
    }

    template <typename PWM>
    concept PwmConcept = requires { typename PWM::pwm_token; };
}

// template <TIM_HandleTypeDef* _handle, uint32_t _channel> class PWM {
// public:
//     template <Mode mode> static inline void start(uint32_t* buffer = nullptr, uint16_t length =
//     0) {
//         if (mode == Mode::Normal) HAL_TIM_PWM_Start(_handle, _channel);
//         else if (mode == Mode::It) HAL_TIM_PWM_Start_IT(_handle, _channel);
//         else if (mode == Mode::Dma) HAL_TIM_PWM_Start_DMA(_handle, _channel, buffer, length);
//     }

//     static inline void set_pwm(uint32_t pwm) { compare_register() = pwm; }

//     static inline void set_ratio(float ratio) { set_pwm(ratio * (_handle->Init.Period)); }

//     static inline uint32_t period() { return _handle->Init.Period; }

//     struct pwm_token { };

// private:
//     // capture/compare register
//     static inline constexpr volatile uint32_t& compare_register() {
//         auto address = &_handle->Instance->CCR1;
//         return *(address + pwm::get_index_from_channel<_channel>() - 1);
//     }
// };

}

// constexpr auto pwm_port = GPIOA;
// constexpr auto pwm_pin = GPIO8;
// constexpr auto pwm_rcc = RCC_GPIOA;

// // TIM1 for PWM generation
// constexpr auto pwm_timer = TIM1;
// constexpr auto pwm_timer_rcc = RCC_TIM1;

// static void clock_setup(void) {
//     rcc_periph_clock_enable(pwm_rcc);
//     rcc_periph_clock_enable(pwm_timer_rcc);
// }

// static void gpio_setup(void) {
//     gpio_set_mode(pwm_port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, pwm_pin);
// }

// static void timer_setup(void) {
//     timer_disable_counter(pwm_timer);

//     timer_set_mode(pwm_timer, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

//     // Set prescaler to get 1MHz timer clock (72MHz / 72 = 1MHz)
//     timer_set_prescaler(pwm_timer, 72 - 1);

//     // Set period for 50Hz PWM (1MHz / 50Hz = 20000 ticks per period)
//     timer_set_period(pwm_timer, 20000 - 1);

//     timer_set_oc_mode(pwm_timer, TIM_OC1, TIM_OCM_PWM1);
//     timer_set_oc_polarity_high(pwm_timer, TIM_OC1);
//     timer_enable_oc_output(pwm_timer, TIM_OC1);

//     timer_enable_break_main_output(pwm_timer);
//     timer_enable_counter(pwm_timer);
// }

// static void set_servo_position(double angle) {
//     uint32_t count = 2000 * std::clamp(angle, 0., 180.) / 180 + 500;
//     timer_set_oc_value(pwm_timer, TIM_OC1, count);
// }

// static void delay_ms(uint32_t ms) {
//     for (uint32_t ticks = 0; ticks < 2400 * ms; ticks++)
//         __asm__("nop");
// }