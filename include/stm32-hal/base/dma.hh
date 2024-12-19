#pragma once
#include <libopencm3/stm32/dma.h>

#include "stm32-hal/base/gpio.hh"
#include "stm32-hal/base/timer.hh"
#include "stm32-hal/base/usart.hh"

namespace hal::dma {
template <uint32_t _dma, uint8_t _channel, uint32_t _address> class DmaImpl;
template <uint32_t _dma, uint8_t _channel> struct interface;

using nvic_of_this_dma_channel_is_not_supported = char*;

template <uint32_t _address> using _11 = DmaImpl<DMA1, DMA_CHANNEL1, _address>;
template <> struct interface<DMA1, DMA_CHANNEL1> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL1_IRQ;
};
template <uint32_t _address> using _12 = DmaImpl<DMA1, DMA_CHANNEL2, _address>;
template <> struct interface<DMA1, DMA_CHANNEL2> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL2_IRQ;
};
template <uint32_t _address> using _13 = DmaImpl<DMA1, DMA_CHANNEL3, _address>;
template <> struct interface<DMA1, DMA_CHANNEL3> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL3_IRQ;
};
template <uint32_t _address> using _14 = DmaImpl<DMA1, DMA_CHANNEL4, _address>;
template <> struct interface<DMA1, DMA_CHANNEL4> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL4_IRQ;
};
template <uint32_t _address> using _15 = DmaImpl<DMA1, DMA_CHANNEL5, _address>;
template <> struct interface<DMA1, DMA_CHANNEL5> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL5_IRQ;
};
template <uint32_t _address> using _16 = DmaImpl<DMA1, DMA_CHANNEL6, _address>;
template <> struct interface<DMA1, DMA_CHANNEL6> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL6_IRQ;
};
template <uint32_t _address> using _17 = DmaImpl<DMA1, DMA_CHANNEL7, _address>;
template <> struct interface<DMA1, DMA_CHANNEL7> {
    static constexpr rcc_periph_clken rcc = RCC_DMA1;
    static constexpr uint8_t nvic = NVIC_DMA1_CHANNEL7_IRQ;
};
template <uint32_t _address> using _21 = DmaImpl<DMA2, DMA_CHANNEL1, _address>;
template <> struct interface<DMA2, DMA_CHANNEL1> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    static constexpr uint8_t nvic = NVIC_DMA2_CHANNEL1_IRQ;
};
template <uint32_t _address> using _22 = DmaImpl<DMA2, DMA_CHANNEL2, _address>;
template <> struct interface<DMA2, DMA_CHANNEL2> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    static constexpr uint8_t nvic = NVIC_DMA2_CHANNEL2_IRQ;
};
template <uint32_t _address> using _23 = DmaImpl<DMA2, DMA_CHANNEL3, _address>;
template <> struct interface<DMA2, DMA_CHANNEL3> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    static constexpr uint8_t nvic = NVIC_DMA2_CHANNEL3_IRQ;
};
template <uint32_t _address> using _24 = DmaImpl<DMA2, DMA_CHANNEL4, _address>;
template <> struct interface<DMA2, DMA_CHANNEL4> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    /// @todo check if this is correct
    static constexpr uint8_t nvic = NVIC_DMA2_CHANNEL4_5_IRQ;
};
template <uint32_t _address> using _25 = DmaImpl<DMA2, DMA_CHANNEL5, _address>;
template <> struct interface<DMA2, DMA_CHANNEL5> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    static constexpr uint8_t nvic = NVIC_DMA2_CHANNEL5_IRQ;
};
template <uint32_t _address> using _26 = DmaImpl<DMA2, DMA_CHANNEL6, _address>;
template <> struct interface<DMA2, DMA_CHANNEL6> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
};
template <uint32_t _address> using _27 = DmaImpl<DMA2, DMA_CHANNEL7, _address>;
template <> struct interface<DMA2, DMA_CHANNEL7> {
    static constexpr rcc_periph_clken rcc = RCC_DMA2;
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
};

template <typename _peripheral> struct check {
    using unsupport_preset_and_use_manual_method_please = void;
};

#if defined(STM32F1)
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
public:
    static void setup() { rcc_periph_clock_enable(interface<_dma, _channel>::rcc); }
    struct irq {
        static void enable() {
            constexpr auto nvic = interface<_dma, _channel>::nvic;
            static_assert(nvic != NVIC_IRQ_COUNT, "nvic of this dma channel is not supported");
            nvic_enable_irq(nvic);
        }
        static void enable(uint8_t priority) {
            constexpr auto nvic = interface<_dma, _channel>::nvic;
            static_assert(nvic != NVIC_IRQ_COUNT, "nvic of this dma channel is not supported");
            nvic_set_priority(nvic, priority);
            nvic_enable_irq(nvic);
        }
        static void disable() {
            constexpr auto nvic = interface<_dma, _channel>::nvic;
            static_assert(nvic != NVIC_IRQ_COUNT, "nvic of this dma channel is not supported");
            nvic_disable_irq(nvic);
        }
        struct transfer_error {
            static void enable_with_nvic(uint8_t priority) {
                enable(priority), dma_enable_transfer_error_interrupt(_dma, _channel);
            }
            static void enable_with_nvic() {
                enable(), dma_enable_transfer_error_interrupt(_dma, _channel);
            }
            static void enable_without_nvic() {
                dma_enable_transfer_error_interrupt(_dma, _channel);
            }
            static void disable() { dma_disable_transfer_error_interrupt(_dma, _channel); }
        };
        struct half_transfer {
            static void enable_with_nvic(uint8_t priority) {
                enable(priority), dma_enable_half_transfer_interrupt(_dma, _channel);
            }
            static void enable_with_nvic() {
                enable(), dma_enable_half_transfer_interrupt(_dma, _channel);
            }
            static void enable_without_nvic() {
                dma_enable_half_transfer_interrupt(_dma, _channel);
            }
            static void disable() { dma_disable_half_transfer_interrupt(_dma, _channel); }
        };
        struct transfer_complete {
            static void enable_with_nvic(uint8_t priority) {
                enable(priority), dma_enable_transfer_complete_interrupt(_dma, _channel);
            }
            static void enable_with_nvic() {
                enable(), dma_enable_transfer_complete_interrupt(_dma, _channel);
            }
            static void enable_without_nvic() {
                dma_enable_transfer_complete_interrupt(_dma, _channel);
            }
            static void disable() { dma_disable_transfer_complete_interrupt(_dma, _channel); }
        };
    };

    struct io {
    private:
        template <uint16_t _peripheral, uint16_t _memory, uint16_t _priority> struct write_ {
            static void load(const char* data, std::size_t length) {
                dma_channel_reset(_dma, _channel);

                dma_set_peripheral_address(_dma, _channel, (USART2_BASE + 0x04));
                dma_set_memory_address(_dma, _channel, (uint32_t)data);
                dma_set_number_of_data(_dma, _channel, length);
                dma_set_read_from_memory(_dma, _channel);
                dma_enable_memory_increment_mode(_dma, _channel);

                dma_set_peripheral_size(_dma, _channel, DMA_CCR_PSIZE_8BIT);
                dma_set_memory_size(_dma, _channel, DMA_CCR_MSIZE_8BIT);
                dma_set_priority(_dma, _channel, DMA_CCR_PL_VERY_HIGH);

                dma_enable_transfer_complete_interrupt(_dma, _channel);

                dma_enable_channel(_dma, _channel);
            }

            template <std::size_t n> static void load(const char (&data)[n]) { load(data, n); }
        };

        template <uint16_t _peripheral, uint16_t _memory> struct priority_ {
            using priority_levels_low = write_<_peripheral, _memory, DMA_CCR_PL_LOW>;
            using priority_levels_medium = write_<_peripheral, _memory, DMA_CCR_PL_MEDIUM>;
            using priority_levels_high = write_<_peripheral, _memory, DMA_CCR_PL_HIGH>;
        };

        template <uint16_t _peripheral> struct memory_size_ {
            using memory_8bit = priority_<_peripheral, DMA_CCR_MSIZE_8BIT>;
            using memory_16bit = priority_<_peripheral, DMA_CCR_MSIZE_16BIT>;
            using memory_32bit = priority_<_peripheral, DMA_CCR_MSIZE_32BIT>;
        };

    public:
        struct write {
            using peripheral_8bit = memory_size_<DMA_CCR_PSIZE_8BIT>;
            using peripheral_16bit = memory_size_<DMA_CCR_PSIZE_16BIT>;
            using peripheral_32bit = memory_size_<DMA_CCR_PSIZE_32BIT>;
        };
    };

    static void enable() { dma_enable_channel(_dma, _channel); }
    static void disable() { dma_disable_channel(_dma, _channel); }

    struct attribute {
        static constexpr uint32_t dma = _dma;
        static constexpr uint8_t channel = _channel;
        static constexpr uint32_t address = _address;
        struct dma_token { };
    };
};

}
