#pragma once
#include <libopencm3/stm32/dma.h>

#include "stm32-hal/base/gpio.hh"
#include "stm32-hal/base/timer.hh"
#include "stm32-hal/base/usart.hh"

namespace hal::dma {
template <uint32_t _dma, uint8_t _channel, uint32_t _address> class DmaImpl;
template <uint32_t _dma> struct interface;

template <uint32_t _address> using _11 = DmaImpl<DMA1, DMA_CHANNEL1, _address>;
template <uint32_t _address> using _12 = DmaImpl<DMA1, DMA_CHANNEL2, _address>;
template <uint32_t _address> using _13 = DmaImpl<DMA1, DMA_CHANNEL3, _address>;
template <uint32_t _address> using _14 = DmaImpl<DMA1, DMA_CHANNEL4, _address>;
template <uint32_t _address> using _15 = DmaImpl<DMA1, DMA_CHANNEL5, _address>;
template <uint32_t _address> using _16 = DmaImpl<DMA1, DMA_CHANNEL6, _address>;
template <uint32_t _address> using _17 = DmaImpl<DMA1, DMA_CHANNEL7, _address>;
template <uint32_t _address> using _21 = DmaImpl<DMA2, DMA_CHANNEL1, _address>;
template <uint32_t _address> using _22 = DmaImpl<DMA2, DMA_CHANNEL2, _address>;
template <uint32_t _address> using _23 = DmaImpl<DMA2, DMA_CHANNEL3, _address>;
template <uint32_t _address> using _24 = DmaImpl<DMA2, DMA_CHANNEL4, _address>;
template <uint32_t _address> using _25 = DmaImpl<DMA2, DMA_CHANNEL5, _address>;
template <uint32_t _address> using _26 = DmaImpl<DMA2, DMA_CHANNEL6, _address>;
template <uint32_t _address> using _27 = DmaImpl<DMA2, DMA_CHANNEL7, _address>;

template <typename _peripheral> struct check {
    using unsupport_preset_and_use_manual_method_please = void;
};

#if defined(STM32F1)
template <> struct interface<DMA1> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
};
template <> struct interface<DMA2> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
};

template <> struct check<usart::_1> {
    struct available {
        using write = _14<USART1 + 0x04>;
        using read = _15<USART1 + 0x04>;
    };
};
template <> struct check<usart::_2> {
    struct available {
        using write = _17<USART2 + 0x04>;
        using read = _16<USART2 + 0x04>;
    };
};
template <> struct check<usart::_3> {
    struct available {
        using write = _12<USART3 + 0x04>;
        using read = _13<USART3 + 0x04>;
    };
};
/// @todo add i2c, spi, tim
#endif

template <uint32_t _dma, uint8_t _channel, uint32_t _address> struct DmaImpl {
private:
    struct channel_ { };

public:
    static void setup() { rcc_periph_clock_enable(interface<_dma>::rcc); }
};

}
