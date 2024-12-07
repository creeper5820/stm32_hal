#pragma once

#include <cstdint>

#include <libopencm3/stm32/gpio.h>

namespace hal {
namespace internal {
    // @brief calculate the address of the pin while compiling
    template <uint8_t index> constexpr uint16_t gpio_pin() {
        static_assert(index < 16 && index > -1, "天呐! 你的PIN是不存在的!");
        return (0x0001 * (1 << index % 4)) << (index & ~0b11);
    }

    struct gpio_mode {
        static constexpr auto input = 0;
        struct output {
            static constexpr auto mhz_10 = 1;
            static constexpr auto mhz_2 = 2;
            static constexpr auto mhz_50 = 3;
        };
    };
    struct gpio_config {
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

    // @brief internal class GPIO
    template <uint32_t _port, uint16_t _pin> class GPIO {
    private:
        template <uint8_t _config> struct mode_ {
            static inline void input() { gpio_set_mode(_port, gpio_mode::input, _config, _pin); }
            static inline void output_10_mhz() {
                gpio_set_mode(_port, gpio_mode::output::mhz_10, _config, _pin);
            }
            static inline void output_2_mhz() {
                gpio_set_mode(_port, gpio_mode::output::mhz_2, _config, _pin);
            }
            static inline void output_50_mhz() {
                gpio_set_mode(_port, gpio_mode::output::mhz_50, _config, _pin);
            }
        };

    public:
        struct setup {
            struct config {
                struct input_analog {
                    using mode = mode_<gpio_config::input::analog>;
                };
                struct input_floating {
                    using mode = mode_<gpio_config::input::floating>;
                };
                struct input_pullupdown {
                    using mode = mode_<gpio_config::input::pullupdown>;
                };
                struct output_pushpull {
                    using mode = mode_<gpio_config::output::pushpull>;
                };
                struct output_opendrain {
                    using mode = mode_<gpio_config::output::opendrain>;
                };
                struct output_altfn_pushpull {
                    using mode = mode_<gpio_config::output::altfn_pushpull>;
                };
                struct output_altfn_opendrain {
                    using mode = mode_<gpio_config::output::altfn_opendrain>;
                };
            };
        };

        static inline void setup(const auto&& mode, const auto&& config) {
            gpio_set_mode(_port, mode, config, _pin);
        }

        struct templates {
            static inline void normal() {
                GPIO<_port, _pin>::setup::output_pushpull::output_50_mhz();
            }
        };

    public:
        enum class Status : bool { SET = 0, RESET = 1 };

        struct gpio_token { };

        static inline void set() { gpio_set(_port, _pin); }
        static inline void reset() { gpio_clear(_port, _pin); }
        static inline void toggle() { gpio_toggle(_port, _pin); }
        static inline Status status() { return static_cast<Status>(gpio_get(_port, _pin)); }
    };
}

namespace gpio {
#ifdef GPIO_PORT_A_BASE
    template <uint8_t pin> using PA = internal::GPIO<GPIO_PORT_A_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIO_PORT_B_BASE
    template <uint8_t pin> using PB = internal::GPIO<GPIO_PORT_B_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIO_PORT_C_BASE
    template <uint8_t pin> using PC = internal::GPIO<GPIO_PORT_C_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIO_PORT_D_BASE
    template <uint8_t pin> using PD = internal::GPIO<GPIO_PORT_D_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIO_PORT_E_BASE
    template <uint8_t pin> using PE = internal::GPIO<GPIO_PORT_E_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIO_PORT_F_BASE
    template <uint8_t pin> using PF = internal::GPIO<GPIO_PORT_F_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIO_PORT_G_BASE
    template <uint8_t pin> using PG = internal::GPIO<GPIO_PORT_G_BASE, internal::gpio_pin<pin>()>;
#endif

    using mode = internal::gpio_mode;
    using config = internal::gpio_config;

    template <typename gpio>
    concept GpioConcept = requires { typename gpio::gpio_token; };

    inline void set(GpioConcept auto&... gpio) { (gpio.set(), ...); }
    inline void reset(GpioConcept auto&... gpio) { (gpio.reset(), ...); }
    inline void toggle(GpioConcept auto&... gpio) { (gpio.toggle(), ...); }

}
}
