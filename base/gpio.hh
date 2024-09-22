#pragma once

#include "interface.hh"

namespace hal {

namespace internal {

    // @brief calculate the address of the pin while compiling
    template <uint8_t index>
    constexpr uint16_t gpio_pin() {
        static_assert(index < 16 && index > -1, "天呐! 你的PIN是不存在的!");
        return (0x0001 * (1 << index % 4)) << (index & ~0b11);
    }

    // @brief internal class GPIO
    template <uint32_t port, uint16_t pin>
    class GPIO {
    public:
        enum class Status : bool {
            SET = 0,
            RESET = 1
        };

        inline void set() {
            reinterpret_cast<GPIO_TypeDef*>(port)->BSRR = pin;
        }

        inline void reset() {
            reinterpret_cast<GPIO_TypeDef*>(port)->BSRR = (uint32_t)pin << 16U;
        }

        inline void toggle() {
            reinterpret_cast<GPIO_TypeDef*>(port)->BSRR
                = ((reinterpret_cast<GPIO_TypeDef*>(port)->ODR & pin) << 16U)
                | (~reinterpret_cast<GPIO_TypeDef*>(port)->ODR & pin);
        }

        inline Status status() {
            return static_cast<Status>((reinterpret_cast<GPIO_TypeDef*>(port)->IDR & pin) != (uint32_t)0);
        }

        struct gpio_token { };
    };
}

namespace gpio {
#ifdef GPIOA_BASE
    template <uint8_t pin>
    using PA = internal::GPIO<GPIOA_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOB_BASE
    template <uint8_t pin>
    using PB = internal::GPIO<GPIOB_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOC_BASE
    template <uint8_t pin>
    using PC = internal::GPIO<GPIOC_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOD_BASE
    template <uint8_t pin>
    using PD = internal::GPIO<GPIOD_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOE_BASE
    template <uint8_t pin>
    using PE = internal::GPIO<GPIOE_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOF_BASE
    template <uint8_t pin>
    using PF = internal::GPIO<GPIOF_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOG_BASE
    template <uint8_t pin>
    using PG = internal::GPIO<GPIOG_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOH_BASE
    template <uint8_t pin>
    using PH = internal::GPIO<GPIOH_BASE, internal::gpio_pin<pin>()>;
#endif

    template <typename GPIO>
    concept gpio_concept = requires { typename GPIO::gpio_token; };

    inline void set(gpio_concept auto&... gpio) {
        (gpio.set(), ...);
    }
    inline void reset(gpio_concept auto&... gpio) {
        (gpio.reset(), ...);
    }
    inline void toggle(gpio_concept auto&... gpio) {
        (gpio.toggle(), ...);
    }
}
}
