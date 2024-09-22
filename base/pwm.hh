#pragma once

#ifdef TIM_HandleTypeDef

#include "main.h"
#include "tim.h"
#include <cassert>
#include <cstdint>
#include <cstring>

namespace base {
class PWM {
private:
    TIM_HandleTypeDef* htim_;
    uint32_t channel_;

public:
    enum class Mode {
        Normal = 0,
        DMA,
        IT,
    };

    PWM(TIM_HandleTypeDef* htim, uint32_t channel)
        : htim_(htim)
        , channel_(channel)
    {
        HAL_TIM_PWM_Start(htim_, channel_);
    }

    template <Mode mode>
    void init(const uint32_t* buffer = nullptr, uint16_t length = 0)
    {
        if constexpr (mode == Mode::Normal) {
            HAL_TIM_PWM_Start(htim_, channel_);
        } else if constexpr (mode == Mode::DMA) {
            assert(buffer != nullptr);
            assert(length != 0);
            HAL_TIM_PWM_Start_DMA(htim_, channel_, buffer, length);
        } else if (mode == Mode::IT) {
            HAL_TIM_PWM_Start_IT(htim_, channel_);
        }
    }

    void set_pwm(const uint32_t& pwm)
    {
        if (pwm > htim_->Init.Period)
            return;

        __HAL_TIM_SET_COMPARE(htim_, channel_, pwm);
    }

    void limit(float& ratio, float limit)
    {
        if (ratio > limit)
            ratio = limit;

        if (ratio < -limit)
            ratio = -limit;
    }

    void set_pwm_ratio(float& ratio)
    {
        limit(ratio, 1);
        __HAL_TIM_SET_COMPARE(htim_, channel_, ratio * (htim_->Init.Period));
    }

    uint32_t period() const noexcept
    {
        return htim_->Init.Period;
    }
};
} // namespace base

#endif