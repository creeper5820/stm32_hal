#pragma once

#include "interface.hh"

#include <cassert>
#include <cstdint>

namespace hal {

namespace time {
    inline void delay(uint32_t ms) {
        uint32_t start = ::uwTick;
        uint32_t wait = ms - 1;
        if (wait < HAL_MAX_DELAY)
            wait += static_cast<uint32_t>(::uwTickFreq);
        while (::uwTick - start < wait)
            ;
    }
}

#ifdef HAL_TIM_MODULE_ENABLED

namespace time {
    template <TIM_HandleTypeDef* _htim>
    inline void delay(uint32_t tick) {
        _htim->Instance->CNT = 0;
        HAL_TIM_Base_Start(_htim);
        while (_htim->Instance->CNT < tick)
            ;
        HAL_TIM_Base_Stop(_htim);
    }
}

template <TIM_HandleTypeDef* _timer>
class Timer {
public:
    using Callback = void (*)(void);

    static inline void start() { HAL_TIM_Base_Start_IT(_timer); }

    static inline void stop() { HAL_TIM_Base_Stop_IT(_timer); }

    static inline void callback(TIM_HandleTypeDef* htim) {
        if (htim != _timer)
            return;
        for (int index = 0; index < activity_size_; index++) {
            auto& activity = activities_[index];
            if (count_tick_ % activity.tick == 0)
                activity.callback();
        }
        count_tick_++;
    }

    static inline void register_activity(uint16_t tick, Callback callback) {
        activities_[activity_size_] = { callback, tick };
        activity_size_++;
    }

private:
    static inline struct {
        Callback callback;
        uint16_t tick;
    } activities_[20];

    static inline uint64_t count_tick_ = 0;
    static inline uint16_t activity_size_ = 0;
};

#endif
} // namespace base
