#pragma once

#include "interface.hh"

#include <cassert>
#include <concepts>
#include <cstdint>

namespace hal {

using TimHandler = TIM_HandleTypeDef*;

namespace time {
    inline void delay(uint32_t ms) {
        uint32_t start = ::uwTick;
        uint32_t wait = ms - 1;
        if (wait < HAL_MAX_DELAY) wait += static_cast<uint32_t>(::uwTickFreq);
        while (::uwTick - start < wait)
            ;
    }
}

#ifdef HAL_TIM_MODULE_ENABLED

namespace time {
    template <TIM_HandleTypeDef* _htim> inline void delay(uint32_t tick) {
        _htim->Instance->CNT = 0;
        HAL_TIM_Base_Start(_htim);
        while (_htim->Instance->CNT < tick)
            ;
        HAL_TIM_Base_Stop(_htim);
    }
}

template <TIM_HandleTypeDef* _timer> class Timer {
public:
    using Callback = void (*)(void);

    static inline void start() { HAL_TIM_Base_Start_IT(_timer); }

    static inline void stop() { HAL_TIM_Base_Stop_IT(_timer); }

    static inline void callback(TIM_HandleTypeDef* htim) {
        if (htim != _timer) return;
        for (int index = 0; index < activity_size_; index++) {
            auto& activity = activities_[index];
            if (count_tick_ % activity.tick == 0) activity.callback();
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

namespace internal {

    template <typename Handlers>
    concept TimerStaticCallableConcept = requires(Handlers, TimHandler htim) {
        { Handlers::callback(htim) } -> std::same_as<void>;
    };
    template <typename Handler>
    concept TimerNormalCallableConcept = requires(Handler handler, TimHandler htim) {
        { handler.callback(htim) } -> std::same_as<void>;
    };
    template <typename Handler>
    concept TimerDirectCallableConcept = requires(Handler handler, TimHandler htim) {
        { handler(htim) } -> std::same_as<void>;
    };
    template <typename Handlers>
    concept TimerDirectCallableNoArgsConcept = requires(Handlers handler) {
        { handler() } -> std::same_as<void>;
    };

    void call_timer_callback(TimHandler htim, TimerStaticCallableConcept auto const& handler) {
        handler.callback(htim);
    }
    void call_timer_callback(TimHandler htim, TimerNormalCallableConcept auto&& handler) {
        handler.callback(htim);
    }
    void call_timer_callback(TimHandler htim, TimerDirectCallableConcept auto&& handler) {
        handler(htim);
    }
    void call_timer_callback(TimHandler, TimerDirectCallableNoArgsConcept auto&& handler) {
        handler();
    }

    void execute_timer_callbacks(TimHandler htim, auto&&... handlers) {
        (call_timer_callback(htim, std::forward<decltype(handlers)>(handlers)), ...);
    }
}

#define GENERATE_TIM_PERIOD_ELAPSED_CALLBACK(...)                                                  \
    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {                                  \
        hal::internal::execute_timer_callbacks(htim, __VA_ARGS__);                                 \
    }

#endif
}