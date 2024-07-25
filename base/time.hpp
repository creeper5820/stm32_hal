#pragma once

#include "stm32f4xx_hal.h"
#include <cstdint>

namespace base {
class Delay {
private:
    uint8_t factor_us_;
    uint16_t factor_ms_;

public:
    Delay()
    {
    }

    // TODO
    void us(uint16_t delay)
    {
        (void)delay;
    }

    void ms(uint32_t delay)
    {
        HAL_Delay(delay - 1);
    }
};

}

inline base::Delay delay = base::Delay();