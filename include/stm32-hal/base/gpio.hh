#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

namespace hal {
namespace gpio {
    template <uint32_t _port, uint16_t _pin> class GpioImpl;
    template <uint32_t _port> constexpr rcc_periph_clken gpio_rcc();

    /// @brief calculate the address of the pin while compiling
    template <uint8_t index> constexpr uint16_t gpio_pin() {
        static_assert(index < 16 && index > -1, "unknown gpio pin");
        return (0x0001 * (1 << index % 4)) << (index & ~0b11);
    }

#ifdef GPIO_PORT_A_BASE
    template <uint8_t pin> using pa = GpioImpl<GPIO_PORT_A_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_A_BASE>() { return RCC_GPIOA; }
#endif
#ifdef GPIO_PORT_B_BASE
    template <uint8_t pin> using pb = GpioImpl<GPIO_PORT_B_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_B_BASE>() { return RCC_GPIOB; }
#endif
#ifdef GPIO_PORT_C_BASE
    template <uint8_t pin> using pc = GpioImpl<GPIO_PORT_C_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_C_BASE>() { return RCC_GPIOC; }
#endif
#ifdef GPIO_PORT_D_BASE
    template <uint8_t pin> using pd = GpioImpl<GPIO_PORT_D_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_D_BASE>() { return RCC_GPIOD; }
#endif
#ifdef GPIO_PORT_E_BASE
    template <uint8_t pin> using pe = GpioImpl<GPIO_PORT_E_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_E_BASE>() { return RCC_GPIOE; }
#endif
#ifdef GPIO_PORT_F_BASE
    template <uint8_t pin> using pf = GpioImpl<GPIO_PORT_F_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_F_BASE>() { return RCC_GPIOF; }
#endif
#ifdef GPIO_PORT_G_BASE
    template <uint8_t pin> using pg = GpioImpl<GPIO_PORT_G_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_G_BASE>() { return RCC_GPIOG; }
#endif

    /// @brief internal class GPIO
    template <uint32_t _port, uint16_t _pin> class GpioImpl {
    private:
        static void enable_rcc() { rcc_periph_clock_enable(gpio_rcc<_port>()); }

        template <uint8_t _config> struct mode_ {
            static void input() {
                enable_rcc(), gpio_set_mode(_port, GPIO_MODE_INPUT, _config, _pin);
            }
            static void output_10mhz() {
                enable_rcc(), gpio_set_mode(_port, GPIO_MODE_OUTPUT_10_MHZ, _config, _pin);
            }
            static void output_02mhz() {
                enable_rcc(), gpio_set_mode(_port, GPIO_MODE_OUTPUT_2_MHZ, _config, _pin);
            }
            static void output_50mhz() {
                enable_rcc(), gpio_set_mode(_port, GPIO_MODE_OUTPUT_50_MHZ, _config, _pin);
            }
        };

    public:
        struct setup {
            using input_analog = mode_<GPIO_CNF_INPUT_ANALOG>;
            using input_float = mode_<GPIO_CNF_INPUT_FLOAT>;
            using input_pullupdown = mode_<GPIO_CNF_INPUT_PULL_UPDOWN>;
            using output_pushpull = mode_<GPIO_CNF_OUTPUT_PUSHPULL>;
            using output_opendrain = mode_<GPIO_CNF_OUTPUT_OPENDRAIN>;
            using output_altfn_pushpull = mode_<GPIO_CNF_OUTPUT_ALTFN_PUSHPULL>;
            using output_altfn_opendrain = mode_<GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN>;

            struct templates {
                static void normal() { setup::output_pushpull::output_50mhz(); }
                static void usart_tx() { setup::output_altfn_pushpull::output_50mhz(); }
                static void usart_rx() { setup::input_float::input(); }
            };
        };

        static void set() { gpio_set(_port, _pin); }
        static void reset() { gpio_clear(_port, _pin); }
        static void toggle() { gpio_toggle(_port, _pin); }

        /// @todo check if this is correct
        static uint16_t status() { return gpio_get(_port, _pin); }

        struct attribute {
            static constexpr uint32_t port = _port;
            static constexpr uint16_t pin = _pin;
            struct gpio_token { };
        };
    };
}

template <typename gpio>
concept gpio_concept = requires { typename gpio::attribute::gpio_token; };

inline void set(gpio_concept auto&... gpio) { (gpio.set(), ...); }
inline void reset(gpio_concept auto&... gpio) { (gpio.reset(), ...); }
inline void toggle(gpio_concept auto&... gpio) { (gpio.toggle(), ...); }

}
