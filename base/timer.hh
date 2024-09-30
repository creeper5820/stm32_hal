#pragma once

#include "interface.hh"

#include <array>
#include <cassert>
#include <cstdint>

namespace hal::time {

constexpr size_t activity_limit = 10;

inline void delay(uint32_t ms) {
    uint32_t start = ::uwTick;
    uint32_t wait = ms - 1;
    if (wait < HAL_MAX_DELAY)
        wait += static_cast<uint32_t>(::uwTickFreq);
    while (::uwTick - start < wait)
        ;
}

#ifdef HAL_TIM_MODULE_ENABLED
inline void delay(TIM_HandleTypeDef* htim, uint32_t tick) {
    htim->Instance->CNT = 0;
    HAL_TIM_Base_Start(htim);

    while (htim->Instance->CNT < tick)
        ;

    HAL_TIM_Base_Stop(htim);
}

class Timer {
public:
    using Callback = void (*)(void);

    Timer(TIM_HandleTypeDef* htim)
        : htim_(htim) {
    }

    void start() { HAL_TIM_Base_Start_IT(htim_); }

    void stop() { HAL_TIM_Base_Stop_IT(htim_); }

    void callback(TIM_HandleTypeDef* htim) {
        if (htim != htim_)
            return;

        count_tick_++;

        for (int i = 0; i < activity_size_; i++) {
            if (count_tick_ % activity_array_[i].tick == 0)
                activity_array_[i].callback();
        }
    }

    void register_activity(uint16_t tick, Callback callback) {
        assert(activity_size_ < activity_limit);

        activity_size_++;

        activity_array_[activity_size_ - 1].callback = callback;
        activity_array_[activity_size_ - 1].tick = tick;
    }

private:
    struct Activity {
        Callback callback;
        uint16_t tick;
    };

private:
    TIM_HandleTypeDef* htim_;
    std::array<Activity, activity_limit> activity_array_;
    uint64_t count_tick_ = 0;
    uint8_t activity_size_ = 0;
};

#endif
} // namespace base
