#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

namespace hal {
namespace gpio {
    template <uint32_t _port, uint16_t _pin> class Gpio;
    template <uint32_t _port> constexpr rcc_periph_clken gpio_rcc();

    /// @brief calculate the address of the pin while compiling
    template <uint8_t index> constexpr uint16_t gpio_pin() {
        static_assert(index < 16 && index > -1, "unknown gpio pin");
        return (0x0001 * (1 << index % 4)) << (index & ~0b11);
    }

#ifdef GPIO_PORT_A_BASE
    template <uint8_t pin> using PA = Gpio<GPIO_PORT_A_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_A_BASE>() { return RCC_GPIOA; }
#endif
#ifdef GPIO_PORT_B_BASE
    template <uint8_t pin> using PB = Gpio<GPIO_PORT_B_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_B_BASE>() { return RCC_GPIOB; }
#endif
#ifdef GPIO_PORT_C_BASE
    template <uint8_t pin> using PC = Gpio<GPIO_PORT_C_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_C_BASE>() { return RCC_GPIOC; }
#endif
#ifdef GPIO_PORT_D_BASE
    template <uint8_t pin> using PD = Gpio<GPIO_PORT_D_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_D_BASE>() { return RCC_GPIOD; }
#endif
#ifdef GPIO_PORT_E_BASE
    template <uint8_t pin> using PE = Gpio<GPIO_PORT_E_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_E_BASE>() { return RCC_GPIOE; }
#endif
#ifdef GPIO_PORT_F_BASE
    template <uint8_t pin> using PF = Gpio<GPIO_PORT_F_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_F_BASE>() { return RCC_GPIOF; }
#endif
#ifdef GPIO_PORT_G_BASE
    template <uint8_t pin> using PG = Gpio<GPIO_PORT_G_BASE, gpio_pin<pin>()>;
    template <> constexpr rcc_periph_clken gpio_rcc<GPIO_PORT_G_BASE>() { return RCC_GPIOG; }
#endif

    struct mode {
        static constexpr auto input = 0;
        struct output {
            static constexpr auto mhz_10 = 1;
            static constexpr auto mhz_2 = 2;
            static constexpr auto mhz_50 = 3;
        };
    };
    struct config {
        struct input {
            static constexpr auto analog = 0;
            static constexpr auto floating = 1;
            static constexpr auto pullupdown = 2;
        };
        struct output {
            static constexpr auto pushpull = 0;
            static constexpr auto opendrain = 1;
            static constexpr auto altfn_pushpull = 2;
            static constexpr auto altfn_opendrain = 3;
        };
    };

    /// @brief internal class GPIO
    template <uint32_t _port, uint16_t _pin> class Gpio {
    private:
        static inline void enable_rcc() { rcc_periph_clock_enable(gpio_rcc<_port>()); }

        template <uint8_t _config> struct mode_ {
            static inline void input() {
                enable_rcc(), gpio_set_mode(_port, mode::input, _config, _pin);
            }
            static inline void output_10mhz() {
                enable_rcc(), gpio_set_mode(_port, mode::output::mhz_10, _config, _pin);
            }
            static inline void output_02mhz() {
                enable_rcc(), gpio_set_mode(_port, mode::output::mhz_2, _config, _pin);
            }
            static inline void output_50mhz() {
                enable_rcc(), gpio_set_mode(_port, mode::output::mhz_50, _config, _pin);
            }
        };

    public:
        static inline void setup(const auto& mode, const auto& config) {
            gpio_set_mode(_port, mode, config, _pin);
        }

        struct setup {
            using input_analog = mode_<config::input::analog>;
            using input_floating = mode_<config::input::floating>;
            using input_pullupdown = mode_<config::input::pullupdown>;
            using output_pushpull = mode_<config::output::pushpull>;
            using output_opendrain = mode_<config::output::opendrain>;
            using output_altfn_pushpull = mode_<config::output::altfn_pushpull>;
            using output_altfn_opendrain = mode_<config::output::altfn_opendrain>;

            struct templates {
                static inline void normal() {
                    Gpio<_port, _pin>::setup::output_pushpull::output_50mhz();
                }
            };
        };

        enum class Status : bool { SET = 0, RESET = 1 };

        static inline void set() { gpio_set(_port, _pin); }
        static inline void reset() { gpio_clear(_port, _pin); }
        static inline void toggle() { gpio_toggle(_port, _pin); }
        static inline Status status() { return static_cast<Status>(gpio_get(_port, _pin)); }

        struct gpio_token { };
    };
}

template <typename gpio>
concept gpio_concept = requires { typename gpio::gpio_token; };

inline void set(gpio_concept auto&... gpio) { (gpio.set(), ...); }
inline void reset(gpio_concept auto&... gpio) { (gpio.reset(), ...); }
inline void toggle(gpio_concept auto&... gpio) { (gpio.toggle(), ...); }

}
