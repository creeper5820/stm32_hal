#pragma once

#include <cassert>
#include <cstdint>

#ifdef HAL_TIM_MODULE_ENABLED

namespace hal {

template <TIM_HandleTypeDef* _timer> class Encoder {
public:
    static inline void setup(bool direction = true) {
        direction_ = direction;
        HAL_TIM_Encoder_Start(_timer, TIM_CHANNEL_ALL);
        clear();
    }

    static inline int32_t read() { return count_register(); }

    // get and update, be attention to not override the value
    static inline int32_t interval() {
        static int32_t last = read();

        int32_t current = read();
        int32_t value;

        value = current - last;

        if (value < -static_cast<int32_t>(period() / 2)) value += period();
        if (value > static_cast<int32_t>(period() / 2)) value -= period();

        last = current;
        return value * (direction_ ? 1 : -1);
    }

    static inline void clear() { count_register() = 0; }

    static inline void set(uint32_t count) { count_register() = count; }

    static inline void set_direction(bool direction) { direction_ = direction; }

    static inline volatile uint32_t& count_register() { return _timer->Instance->CNT; }
    static inline uint32_t period() { return _timer->Init.Period; }

private:
    static inline bool direction_ = true;
};
}
#endif
