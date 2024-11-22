#pragma once

#include "interface.hh"

#ifdef HAL_GPIO_MODULE_ENABLED

namespace hal {
namespace internal {
    // @brief calculate the address of the pin while compiling
    template <uint8_t index> constexpr uint16_t gpio_pin() {
        static_assert(index < 16 && index > -1, "天呐! 你的PIN是不存在的!");
        return (0x0001 * (1 << index % 4)) << (index & ~0b11);
    }

    // @brief internal class GPIO
    template <uint32_t _port, uint16_t _pin> class GPIO {
    public:
        enum class Status : bool { SET = 0, RESET = 1 };

        struct gpio_token { };

        static inline void set() { pointer()->BSRR = _pin; }
        static inline void reset() { pointer()->BSRR = (uint32_t)_pin << 16U; }
        static inline void toggle() {
            pointer()->BSRR = ((pointer()->ODR & _pin) << 16U) | (~pointer()->ODR & _pin);
        }
        static inline Status status() {
            return static_cast<Status>((pointer()->IDR & _pin) != uint32_t(0));
        }

    private:
        static constexpr GPIO_TypeDef* pointer() { return reinterpret_cast<GPIO_TypeDef*>(_port); }
    };
} // namespace internal

namespace gpio {
#ifdef GPIOA_BASE
    template <uint8_t pin> using PA = internal::GPIO<GPIOA_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOB_BASE
    template <uint8_t pin> using PB = internal::GPIO<GPIOB_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOC_BASE
    template <uint8_t pin> using PC = internal::GPIO<GPIOC_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOD_BASE
    template <uint8_t pin> using PD = internal::GPIO<GPIOD_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOE_BASE
    template <uint8_t pin> using PE = internal::GPIO<GPIOE_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOF_BASE
    template <uint8_t pin> using PF = internal::GPIO<GPIOF_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOG_BASE
    template <uint8_t pin> using PG = internal::GPIO<GPIOG_BASE, internal::gpio_pin<pin>()>;
#endif

#ifdef GPIOH_BASE
    template <uint8_t pin> using PH = internal::GPIO<GPIOH_BASE, internal::gpio_pin<pin>()>;
#endif

    template <typename GPIO>
    concept GpioConcept = requires { typename GPIO::gpio_token; };

    inline void set(GpioConcept auto&... gpio) { (gpio.set(), ...); }
    inline void reset(GpioConcept auto&... gpio) { (gpio.reset(), ...); }
    inline void toggle(GpioConcept auto&... gpio) { (gpio.toggle(), ...); }
} // namespace gpio
} // namespace hal

#endif