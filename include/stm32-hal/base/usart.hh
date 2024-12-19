#pragma once

#include <cstddef>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#include "stm32-hal/base/gpio.hh"

namespace hal::usart {
template <uint32_t _usart> class UsartImpl;
template <uint32_t _usart> struct interface;

#if defined(USART1)
template <> struct interface<USART1> {
    using tx = gpio::GpioImpl<GPIO_BANK_USART1_TX, GPIO_USART1_TX>;
    using rx = gpio::GpioImpl<GPIO_BANK_USART1_RX, GPIO_USART1_RX>;
    static constexpr rcc_periph_clken rcc = RCC_USART1;
    static constexpr rcc_periph_rst rst = RST_USART1;
    static constexpr uint8_t nvic = NVIC_USART1_IRQ;
};
using _1 = UsartImpl<USART1>;
#endif

#if defined(USART2)
template <> struct interface<USART2> {
    using tx = gpio::GpioImpl<GPIO_BANK_USART2_TX, GPIO_USART2_TX>;
    using rx = gpio::GpioImpl<GPIO_BANK_USART2_RX, GPIO_USART2_RX>;
    static constexpr rcc_periph_clken rcc = RCC_USART2;
    static constexpr rcc_periph_rst rst = RST_USART2;
    static constexpr uint8_t nvic = NVIC_USART2_IRQ;
};
using _2 = UsartImpl<USART2>;
#endif

#if defined(USART3)
template <> struct interface<USART3> {
    using tx = gpio::GpioImpl<GPIO_BANK_USART3_TX, GPIO_USART3_TX>;
    using rx = gpio::GpioImpl<GPIO_BANK_USART3_RX, GPIO_USART3_RX>;
    static constexpr rcc_periph_clken rcc = RCC_USART3;
    static constexpr rcc_periph_rst rst = RST_USART3;
    static constexpr uint8_t nvic = NVIC_USART3_IRQ;
};
using _3 = UsartImpl<USART3>;
#endif

#if defined(UART4)
template <> struct interface<UART4> {
    using tx = gpio::GpioImpl<GPIO_BANK_UART4_TX, GPIO_UART4_TX>;
    using rx = gpio::GpioImpl<GPIO_BANK_UART4_RX, GPIO_UART4_RX>;
    static constexpr rcc_periph_clken rcc = RCC_UART4;
    static constexpr rcc_periph_rst rst = RST_UART4;
    static constexpr uint8_t nvic = NVIC_UART4_IRQ;
};
using _4 = UsartImpl<UART4>;
#endif

#if defined(UART5)
template <> struct interface<UART5> {
    using tx = gpio::GpioImpl<GPIO_BANK_UART5_TX, GPIO_UART5_TX>;
    using rx = gpio::GpioImpl<GPIO_BANK_UART5_RX, GPIO_UART5_RX>;
    static constexpr rcc_periph_clken rcc = RCC_UART5;
    static constexpr rcc_periph_rst rst = RST_UART5;
    static constexpr uint8_t nvic = NVIC_UART5_IRQ;
};
using _5 = UsartImpl<UART5>;
#endif

template <uint32_t _usart> class UsartImpl {
private:
    template <uint32_t _baud, uint32_t _bits, uint32_t stopbits, uint32_t _mode, uint32_t _parity>
    struct flowcontrol_ {
    public:
        static void flowcontrol_none() {
            rcc_periph_clock_enable(interface<_usart>::rcc);
            usart_set_flow_control(_usart, USART_FLOWCONTROL_NONE), internal_setup();
        }
        static void flowcontrol_ready_to_send() {
            rcc_periph_clock_enable(interface<_usart>::rcc);
            usart_set_flow_control(_usart, USART_FLOWCONTROL_RTS), internal_setup();
        }
        static void flowcontrol_clear_to_send() {
            rcc_periph_clock_enable(interface<_usart>::rcc);
            usart_set_flow_control(_usart, USART_FLOWCONTROL_CTS), internal_setup();
        }
        static void flowcontrol_ready_and_clear_to_send() {
            rcc_periph_clock_enable(interface<_usart>::rcc);
            usart_set_flow_control(_usart, USART_FLOWCONTROL_RTS_CTS), internal_setup();
        }

    private:
        static void internal_setup() {
            usart_set_baudrate(_usart, _baud);
            usart_set_databits(_usart, _bits);
            usart_set_stopbits(_usart, stopbits);
            usart_set_mode(_usart, _mode);
            usart_set_parity(_usart, _parity);
            usart_enable(_usart);
        }
    };
    template <uint32_t _baud, uint32_t _bits, uint32_t stopbits, uint32_t _mode> struct parity_ {
        using parity_none = flowcontrol_<_baud, _bits, stopbits, _mode, USART_PARITY_NONE>;
        using parity_even = flowcontrol_<_baud, _bits, stopbits, _mode, USART_PARITY_EVEN>;
        using parity_odd = flowcontrol_<_baud, _bits, stopbits, _mode, USART_PARITY_ODD>;
    };
    template <uint32_t _baud, uint32_t _bits, uint32_t stopbits> struct mode_ {
        using mode_receive = parity_<_baud, _bits, stopbits, USART_MODE_RX>;
        using mode_transmit = parity_<_baud, _bits, stopbits, USART_MODE_TX>;
        using mode_transmit_receive = parity_<_baud, _bits, stopbits, USART_MODE_TX_RX>;
    };
    template <uint32_t _baud, uint32_t _bits> struct stopbits_ {
        using stopbit_0_5 = mode_<_baud, _bits, USART_STOPBITS_0_5>;
        using stopbit_1 = mode_<_baud, _bits, USART_STOPBITS_1>;
        using stopbit_1_5 = mode_<_baud, _bits, USART_STOPBITS_1_5>;
        using stopbit_2 = mode_<_baud, _bits, USART_STOPBITS_2>;
    };
    template <uint32_t _baud> struct databits_ {
        template <uint32_t _bits> using databits = stopbits_<_baud, _bits>;
    };

public:
    struct setup {
        template <uint32_t _baud> using baud = databits_<_baud>;
        struct templates {
            template <uint32_t _baud> static void normal() {
                pin::tx::setup::templates::usart_tx();
                pin::rx::setup::templates::usart_rx();
                /// @todo why it doesn't work
                // setup::baud<_baud>::databits<
                //     8>::stopbit_1::mode_transmit_receive::parity_none::flowcontrol_none();
                stopbits_<_baud, 8>::stopbit_1 //
                    ::mode_transmit_receive //
                    ::parity_none //
                    ::flowcontrol_none();
                irq::receive::enable_with_nvic();
            }
            static void normal115200() { normal<115200>(); }
            static void normal9600() { normal<9600>(); }
        };
    };
    struct pin {
        using tx = interface<_usart>::tx;
        using rx = interface<_usart>::rx;
    };
    struct irq {
        static constexpr uint8_t nvic = interface<_usart>::nvic;
        struct receive {
            static void enable_with_nvic() {
                usart_enable_rx_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_with_nvic(uint8_t priority) {
                nvic_set_priority(nvic, priority);
                usart_enable_rx_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_without_nvic() { usart_enable_rx_interrupt(_usart); }
            static void disable() { usart_disable_rx_interrupt(_usart); }
        };
        struct transmit {
            static void enable_with_nvic() {
                usart_enable_tx_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_with_nvic(uint8_t priority) {
                nvic_set_priority(nvic, priority);
                usart_enable_tx_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_without_nvic() { usart_enable_tx_interrupt(_usart); }
            static void disable() { usart_disable_tx_interrupt(_usart); }
        };
        struct transmit_complete {
            static void enable_with_nvic() {
                usart_enable_tx_complete_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_with_nvic(uint8_t priority) {
                nvic_set_priority(nvic, priority);
                usart_enable_tx_complete_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_without_nvic() { usart_enable_tx_complete_interrupt(_usart); }
            static void disable() { usart_disable_tx_complete_interrupt(_usart); }
        };
        struct idle {
            static void enable_with_nvic() {
                usart_enable_idle_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_with_nvic(uint8_t priority) {
                nvic_set_priority(nvic, priority);
                usart_enable_idle_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_without_nvic() { usart_enable_idle_interrupt(_usart); }
            static void disable() { usart_disable_idle_interrupt(_usart); }
        };
        struct error {
            static void enable_with_nvic() {
                usart_enable_error_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_with_nvic(uint8_t priority) {
                nvic_set_priority(nvic, priority);
                usart_enable_error_interrupt(_usart), nvic_enable_irq(nvic);
            }
            static void enable_without_nvic() { usart_enable_error_interrupt(_usart); }
            static void disable() { usart_disable_error_interrupt(_usart); }
        };
    };
    struct flag {
        struct irq {
            static bool parity_error_enabled() { return usart_get_flag(_usart, USART_CR1_PEIE); }
            static bool transmit_empty_enabled() { return usart_get_flag(_usart, USART_CR1_TXEIE); }
            static bool transmit_complete_enabled() {
                return usart_get_flag(_usart, USART_CR1_TCIE);
            }
            static bool receive_not_empty_enabled() {
                return usart_get_flag(_usart, USART_CR1_RXNEIE);
            }
            static bool idle_enabled() { return usart_get_flag(_usart, USART_SR_IDLE); }
        };
        struct error {
            static bool parity() { return usart_get_flag(_usart, USART_FLAG_PE); }
            static bool framing() { return usart_get_flag(_usart, USART_FLAG_FE); }
            static bool over_run() { return usart_get_flag(_usart, USART_FLAG_ORE); }
#if defined(USART_SR_NF)
            static bool noise() { return usart_get_flag(_usart, USART_FLAG_NF); }
#endif
        };
        static bool usart_enabled() { return usart_get_flag(_usart, USART_CR1_UE); }
        static bool receive_enabled() { return usart_get_flag(_usart, USART_CR1_RE); }
        static bool transmit_enabled() { return usart_get_flag(_usart, USART_CR1_TE); }

        static bool idle() { return usart_get_flag(_usart, USART_FLAG_IDLE); }
        static bool receive_not_empty() { return usart_get_flag(_usart, USART_FLAG_RXNE); };
        static bool transmit_complete() { return usart_get_flag(_usart, USART_FLAG_TC); }
        static bool transmit_empty() { return usart_get_flag(_usart, USART_FLAG_TXE); }
    };

    struct io {
        static uint16_t receive() { return usart_recv(_usart); }
        static void transmit(uint16_t data) { usart_send(_usart, data); }

        static void wait_receive_ready() { usart_wait_recv_ready(_usart); }
        static void wait_transmit_ready() { usart_wait_send_ready(_usart); }

        static uint16_t receive_blocking() { return usart_recv_blocking(_usart); }
        static void transmit_blocking(uint16_t data) { usart_send_blocking(_usart, data); }

        template <std::size_t n> static void transmit_blocking(const char (&data)[n]) {
            for (const auto& bit : data)
                transmit_blocking(bit);
        }

        struct dma {
            struct receive {
                static void enable() { usart_enable_rx_dma(_usart); }
                static void disable() { usart_disable_rx_dma(_usart); }
            };
            struct transmit {
                static void enable() { usart_enable_tx_dma(_usart); }
                static void disable() { usart_disable_tx_dma(_usart); }
            };
        };
    };
    struct attribute {
        static constexpr uint32_t usart = _usart;
        struct usart_token { };
    };
};

template <typename usart>
concept usart_concept = requires {
    typename usart::attribute::usart_token;
    usart::attribute::usart;
};

}