#pragma once

#include "main.h"

namespace hal {

enum class Mode : uint8_t {
    Normal,
    Dma,
    It,
};

enum class Status : uint8_t { Ready = 0x00, Error = 0x01, Busy = 0x02, Timeout = 0x03 };

}