#pragma once

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

namespace hal::timer {
template <uint32_t _peripheral> class Timer;
template <uint32_t _peripheral> constexpr rcc_periph_clken timer_rcc();
template <uint32_t _peripheral> constexpr rcc_periph_rst timer_rst();
template <uint32_t _peripheral> constexpr uint8_t timer_nvic();
template <uint32_t _peripheral> constexpr uint8_t timer_nvic_brk();
template <uint32_t _peripheral> constexpr uint8_t timer_nvic_up();
template <uint32_t _peripheral> constexpr uint8_t timer_nvic_trg_com();
template <uint32_t _peripheral> constexpr uint8_t timer_nvic_cc();

#if defined(TIM1)
using _01 = Timer<TIM1>;
template <> constexpr rcc_periph_clken timer_rcc<TIM1>() { return RCC_TIM1; }
template <> constexpr rcc_periph_rst timer_rst<TIM1>() { return RST_TIM1; }
template <> constexpr uint8_t timer_nvic<TIM1>() {
#ifdef NVIC_TIM1_IRQ
    return NVIC_TIM1_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM1>() {
#ifdef NVIC_TIM1_BRK_IRQ
    return NVIC_TIM1_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM1>() {
#ifdef NVIC_TIM1_UP_IRQ
    return NVIC_TIM1_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM1>() {
#ifdef NVIC_TIM1_TRG_COM_IRQ
    return NVIC_TIM1_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM1>() {
#ifdef NVIC_TIM1_CC_IRQ
    return NVIC_TIM1_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM1

#if defined(TIM2)
using _02 = Timer<TIM2>;
template <> constexpr rcc_periph_clken timer_rcc<TIM2>() { return RCC_TIM2; }
template <> constexpr rcc_periph_rst timer_rst<TIM2>() { return RST_TIM2; }
template <> constexpr uint8_t timer_nvic<TIM2>() {
#ifdef NVIC_TIM2_IRQ
    return NVIC_TIM2_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM2>() {
#ifdef NVIC_TIM2_BRK_IRQ
    return NVIC_TIM2_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM2>() {
#ifdef NVIC_TIM2_UP_IRQ
    return NVIC_TIM2_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM2>() {
#ifdef NVIC_TIM2_TRG_COM_IRQ
    return NVIC_TIM2_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM2>() {
#ifdef NVIC_TIM2_CC_IRQ
    return NVIC_TIM2_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM2

#if defined(TIM3)
using _03 = Timer<TIM3>;
template <> constexpr rcc_periph_clken timer_rcc<TIM3>() { return RCC_TIM3; }
template <> constexpr rcc_periph_rst timer_rst<TIM3>() { return RST_TIM3; }
template <> constexpr uint8_t timer_nvic<TIM3>() {
#ifdef NVIC_TIM3_IRQ
    return NVIC_TIM3_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM3>() {
#ifdef NVIC_TIM3_BRK_IRQ
    return NVIC_TIM3_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM3>() {
#ifdef NVIC_TIM3_UP_IRQ
    return NVIC_TIM3_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM3>() {
#ifdef NVIC_TIM3_TRG_COM_IRQ
    return NVIC_TIM3_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM3>() {
#ifdef NVIC_TIM3_CC_IRQ
    return NVIC_TIM3_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM3

#if defined(TIM4)
using _04 = Timer<TIM4>;
template <> constexpr rcc_periph_clken timer_rcc<TIM4>() { return RCC_TIM4; }
template <> constexpr rcc_periph_rst timer_rst<TIM4>() { return RST_TIM4; }
template <> constexpr uint8_t timer_nvic<TIM4>() {
#ifdef NVIC_TIM4_IRQ
    return NVIC_TIM4_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM4>() {
#ifdef NVIC_TIM4_BRK_IRQ
    return NVIC_TIM4_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM4>() {
#ifdef NVIC_TIM4_UP_IRQ
    return NVIC_TIM4_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM4>() {
#ifdef NVIC_TIM4_TRG_COM_IRQ
    return NVIC_TIM4_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM4>() {
#ifdef NVIC_TIM4_CC_IRQ
    return NVIC_TIM4_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM4

#if defined(TIM5)
using _05 = Timer<TIM5>;
template <> constexpr rcc_periph_clken timer_rcc<TIM5>() { return RCC_TIM5; }
template <> constexpr rcc_periph_rst timer_rst<TIM5>() { return RST_TIM5; }
template <> constexpr uint8_t timer_nvic<TIM5>() {
#ifdef NVIC_TIM5_IRQ
    return NVIC_TIM5_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM5>() {
#ifdef NVIC_TIM5_BRK_IRQ
    return NVIC_TIM5_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM5>() {
#ifdef NVIC_TIM5_UP_IRQ
    return NVIC_TIM5_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM5>() {
#ifdef NVIC_TIM5_TRG_COM_IRQ
    return NVIC_TIM5_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM5>() {
#ifdef NVIC_TIM5_CC_IRQ
    return NVIC_TIM5_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM5

#if defined(TIM6)
using _06 = Timer<TIM6>;
template <> constexpr rcc_periph_clken timer_rcc<TIM6>() { return RCC_TIM6; }
template <> constexpr rcc_periph_rst timer_rst<TIM6>() { return RST_TIM6; }
template <> constexpr uint8_t timer_nvic<TIM6>() {
#ifdef NVIC_TIM6_IRQ
    return NVIC_TIM6_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM6>() {
#ifdef NVIC_TIM6_BRK_IRQ
    return NVIC_TIM6_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM6>() {
#ifdef NVIC_TIM6_UP_IRQ
    return NVIC_TIM6_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM6>() {
#ifdef NVIC_TIM6_TRG_COM_IRQ
    return NVIC_TIM6_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM6>() {
#ifdef NVIC_TIM6_CC_IRQ
    return NVIC_TIM6_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM6

#if defined(TIM7)
using _07 = Timer<TIM7>;
template <> constexpr rcc_periph_clken timer_rcc<TIM7>() { return RCC_TIM7; }
template <> constexpr rcc_periph_rst timer_rst<TIM7>() { return RST_TIM7; }
template <> constexpr uint8_t timer_nvic<TIM7>() {
#ifdef NVIC_TIM7_IRQ
    return NVIC_TIM7_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM7>() {
#ifdef NVIC_TIM7_BRK_IRQ
    return NVIC_TIM7_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM7>() {
#ifdef NVIC_TIM7_UP_IRQ
    return NVIC_TIM7_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM7>() {
#ifdef NVIC_TIM7_TRG_COM_IRQ
    return NVIC_TIM7_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM7>() {
#ifdef NVIC_TIM7_CC_IRQ
    return NVIC_TIM7_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM7

#if defined(TIM8)
using _08 = Timer<TIM8>;
template <> constexpr rcc_periph_clken timer_rcc<TIM8>() { return RCC_TIM8; }
template <> constexpr rcc_periph_rst timer_rst<TIM8>() { return RST_TIM8; }
template <> constexpr uint8_t timer_nvic<TIM8>() {
#ifdef NVIC_TIM8_IRQ
    return NVIC_TIM8_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM8>() {
#ifdef NVIC_TIM8_BRK_IRQ
    return NVIC_TIM8_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM8>() {
#ifdef NVIC_TIM8_UP_IRQ
    return NVIC_TIM8_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM8>() {
#ifdef NVIC_TIM8_TRG_COM_IRQ
    return NVIC_TIM8_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM8>() {
#ifdef NVIC_TIM8_CC_IRQ
    return NVIC_TIM8_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM8

#if defined(TIM9)
using _09 = Timer<TIM9>;
template <> constexpr rcc_periph_clken timer_rcc<TIM9>() { return RCC_TIM9; }
template <> constexpr rcc_periph_rst timer_rst<TIM9>() { return RST_TIM9; }
template <> constexpr uint8_t timer_nvic<TIM9>() {
#ifdef NVIC_TIM9_IRQ
    return NVIC_TIM9_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM9>() {
#ifdef NVIC_TIM9_BRK_IRQ
    return NVIC_TIM9_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM9>() {
#ifdef NVIC_TIM9_UP_IRQ
    return NVIC_TIM9_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM9>() {
#ifdef NVIC_TIM9_TRG_COM_IRQ
    return NVIC_TIM9_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM9>() {
#ifdef NVIC_TIM9_CC_IRQ
    return NVIC_TIM9_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM9

#if defined(TIM10)
using _10 = Timer<TIM10>;
template <> constexpr rcc_periph_clken timer_rcc<TIM10>() { return RCC_TIM10; }
template <> constexpr rcc_periph_rst timer_rst<TIM10>() { return RST_TIM10; }
template <> constexpr uint8_t timer_nvic<TIM10>() {
#ifdef NVIC_TIM10_IRQ
    return NVIC_TIM10_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM10>() {
#ifdef NVIC_TIM10_BRK_IRQ
    return NVIC_TIM10_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM10>() {
#ifdef NVIC_TIM10_UP_IRQ
    return NVIC_TIM10_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM10>() {
#ifdef NVIC_TIM10_TRG_COM_IRQ
    return NVIC_TIM10_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM10>() {
#ifdef NVIC_TIM10_CC_IRQ
    return NVIC_TIM10_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM10

#if defined(TIM11)
using _11 = Timer<TIM11>;
template <> constexpr rcc_periph_clken timer_rcc<TIM11>() { return RCC_TIM11; }
template <> constexpr rcc_periph_rst timer_rst<TIM11>() { return RST_TIM11; }
template <> constexpr uint8_t timer_nvic<TIM11>() {
#ifdef NVIC_TIM11_IRQ
    return NVIC_TIM11_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM11>() {
#ifdef NVIC_TIM11_BRK_IRQ
    return NVIC_TIM11_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM11>() {
#ifdef NVIC_TIM11_UP_IRQ
    return NVIC_TIM11_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM11>() {
#ifdef NVIC_TIM11_TRG_COM_IRQ
    return NVIC_TIM11_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM11>() {
#ifdef NVIC_TIM11_CC_IRQ
    return NVIC_TIM11_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM11

#if defined(TIM12)
using _12 = Timer<TIM12>;
template <> constexpr rcc_periph_clken timer_rcc<TIM12>() { return RCC_TIM12; }
template <> constexpr rcc_periph_rst timer_rst<TIM12>() { return RST_TIM12; }
template <> constexpr uint8_t timer_nvic<TIM12>() {
#ifdef NVIC_TIM12_IRQ
    return NVIC_TIM12_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM12>() {
#ifdef NVIC_TIM12_BRK_IRQ
    return NVIC_TIM12_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM12>() {
#ifdef NVIC_TIM12_UP_IRQ
    return NVIC_TIM12_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM12>() {
#ifdef NVIC_TIM12_TRG_COM_IRQ
    return NVIC_TIM12_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM12>() {
#ifdef NVIC_TIM12_CC_IRQ
    return NVIC_TIM12_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM12

#if defined(TIM13)
using _13 = Timer<TIM13>;
template <> constexpr rcc_periph_clken timer_rcc<TIM13>() { return RCC_TIM13; }
template <> constexpr rcc_periph_rst timer_rst<TIM13>() { return RST_TIM13; }
template <> constexpr uint8_t timer_nvic<TIM13>() {
#ifdef NVIC_TIM13_IRQ
    return NVIC_TIM13_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM13>() {
#ifdef NVIC_TIM13_BRK_IRQ
    return NVIC_TIM13_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM13>() {
#ifdef NVIC_TIM13_UP_IRQ
    return NVIC_TIM13_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM13>() {
#ifdef NVIC_TIM13_TRG_COM_IRQ
    return NVIC_TIM13_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM13>() {
#ifdef NVIC_TIM13_CC_IRQ
    return NVIC_TIM13_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM13

#if defined(TIM14)
using _14 = Timer<TIM14>;
template <> constexpr rcc_periph_clken timer_rcc<TIM14>() { return RCC_TIM14; }
template <> constexpr rcc_periph_rst timer_rst<TIM14>() { return RST_TIM14; }
template <> constexpr uint8_t timer_nvic<TIM14>() {
#ifdef NVIC_TIM14_IRQ
    return NVIC_TIM14_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM14>() {
#ifdef NVIC_TIM14_BRK_IRQ
    return NVIC_TIM14_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM14>() {
#ifdef NVIC_TIM14_UP_IRQ
    return NVIC_TIM14_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM14>() {
#ifdef NVIC_TIM14_TRG_COM_IRQ
    return NVIC_TIM14_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM14>() {
#ifdef NVIC_TIM14_CC_IRQ
    return NVIC_TIM14_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM14

#if defined(TIM15)
using _15 = Timer<TIM15>;
template <> constexpr rcc_periph_clken timer_rcc<TIM15>() { return RCC_TIM15; }
template <> constexpr rcc_periph_rst timer_rst<TIM15>() { return RST_TIM15; }
template <> constexpr uint8_t timer_nvic<TIM15>() {
#ifdef NVIC_TIM15_IRQ
    return NVIC_TIM15_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM15>() {
#ifdef NVIC_TIM15_BRK_IRQ
    return NVIC_TIM15_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM15>() {
#ifdef NVIC_TIM15_UP_IRQ
    return NVIC_TIM15_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM15>() {
#ifdef NVIC_TIM15_TRG_COM_IRQ
    return NVIC_TIM15_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM15>() {
#ifdef NVIC_TIM15_CC_IRQ
    return NVIC_TIM15_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM15

#if defined(TIM16)
using _16 = Timer<TIM16>;
template <> constexpr rcc_periph_clken timer_rcc<TIM16>() { return RCC_TIM16; }
template <> constexpr rcc_periph_rst timer_rst<TIM16>() { return RST_TIM16; }
template <> constexpr uint8_t timer_nvic<TIM16>() {
#ifdef NVIC_TIM16_IRQ
    return NVIC_TIM16_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM16>() {
#ifdef NVIC_TIM16_BRK_IRQ
    return NVIC_TIM16_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM16>() {
#ifdef NVIC_TIM16_UP_IRQ
    return NVIC_TIM16_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM16>() {
#ifdef NVIC_TIM16_TRG_COM_IRQ
    return NVIC_TIM16_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM16>() {
#ifdef NVIC_TIM16_CC_IRQ
    return NVIC_TIM16_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM16

#if defined(TIM17)
using _17 = Timer<TIM17>;
template <> constexpr rcc_periph_clken timer_rcc<TIM17>() { return RCC_TIM17; }
template <> constexpr rcc_periph_rst timer_rst<TIM17>() { return RST_TIM17; }
template <> constexpr uint8_t timer_nvic<TIM17>() {
#ifdef NVIC_TIM17_IRQ
    return NVIC_TIM17_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM17>() {
#ifdef NVIC_TIM17_BRK_IRQ
    return NVIC_TIM17_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM17>() {
#ifdef NVIC_TIM17_UP_IRQ
    return NVIC_TIM17_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM17>() {
#ifdef NVIC_TIM17_TRG_COM_IRQ
    return NVIC_TIM17_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM17>() {
#ifdef NVIC_TIM17_CC_IRQ
    return NVIC_TIM17_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM17

#if defined(TIM21)
using _18 = Timer<TIM18>;
template <> constexpr rcc_periph_clken timer_rcc<TIM18>() { return RCC_TIM18; }
template <> constexpr rcc_periph_rst timer_rst<TIM18>() { return RST_TIM18; }
template <> constexpr uint8_t timer_nvic<TIM18>() {
#ifdef NVIC_TIM18_IRQ
    return NVIC_TIM18_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM18>() {
#ifdef NVIC_TIM18_BRK_IRQ
    return NVIC_TIM18_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM18>() {
#ifdef NVIC_TIM18_UP_IRQ
    return NVIC_TIM18_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM18>() {
#ifdef NVIC_TIM18_TRG_COM_IRQ
    return NVIC_TIM18_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM18>() {
#ifdef NVIC_TIM18_CC_IRQ
    return NVIC_TIM18_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM21

#if defined(TIM22)
using _19 = Timer<TIM19>;
template <> constexpr rcc_periph_clken timer_rcc<TIM19>() { return RCC_TIM19; }
template <> constexpr rcc_periph_rst timer_rst<TIM19>() { return RST_TIM19; }
template <> constexpr uint8_t timer_nvic<TIM19>() {
#ifdef NVIC_TIM19_IRQ
    return NVIC_TIM19_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_brk<TIM19>() {
#ifdef NVIC_TIM19_BRK_IRQ
    return NVIC_TIM19_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_up<TIM19>() {
#ifdef NVIC_TIM19_UP_IRQ
    return NVIC_TIM19_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_trg_com<TIM19>() {
#ifdef NVIC_TIM19_TRG_COM_IRQ
    return NVIC_TIM19_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
template <> constexpr uint8_t timer_nvic_cc<TIM19>() {
#ifdef NVIC_TIM19_CC_IRQ
    return NVIC_TIM19_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}
#endif // TIM22
} // namespace hal::timer
