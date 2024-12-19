#pragma once

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

namespace hal::timer {
template <uint32_t _peripheral> class TimerImpl;
template <uint32_t _peripheral> struct interface;

#if defined(TIM1)
template <> struct interface<TIM1> {
    static constexpr rcc_periph_clken rcc = RCC_TIM1;
    static constexpr rcc_periph_rst rst = RST_TIM1;
#ifdef NVIC_TIM1_IRQ
    static constexpr uint8_t nvic = NVIC_TIM1_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM1_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM1_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM1_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM1_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM1_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM1_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM1_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM1_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _01 = TimerImpl<TIM1>;
#endif // TIM1

#if defined(TIM2)
template <> struct interface<TIM2> {
    static constexpr rcc_periph_clken rcc = RCC_TIM2;
    static constexpr rcc_periph_rst rst = RST_TIM2;
#ifdef NVIC_TIM2_IRQ
    static constexpr uint8_t nvic = NVIC_TIM2_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM2_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM2_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM2_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM2_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM2_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM2_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM2_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM2_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _02 = TimerImpl<TIM2>;
#endif // TIM2

#if defined(TIM3)
template <> struct interface<TIM3> {
    static constexpr rcc_periph_clken rcc = RCC_TIM3;
    static constexpr rcc_periph_rst rst = RST_TIM3;
#ifdef NVIC_TIM3_IRQ
    static constexpr uint8_t nvic = NVIC_TIM3_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM3_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM3_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM3_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM3_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM3_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM3_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM3_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM3_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _03 = TimerImpl<TIM3>;
#endif // TIM3

#if defined(TIM4)
template <> struct interface<TIM4> {
    static constexpr rcc_periph_clken rcc = RCC_TIM4;
    static constexpr rcc_periph_rst rst = RST_TIM4;
#ifdef NVIC_TIM4_IRQ
    static constexpr uint8_t nvic = NVIC_TIM4_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM4_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM4_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM4_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM4_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM4_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM4_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM4_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM4_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _04 = TimerImpl<TIM4>;
#endif // TIM4

#if defined(TIM5)
template <> struct interface<TIM5> {
    static constexpr rcc_periph_clken rcc = RCC_TIM5;
    static constexpr rcc_periph_rst rst = RST_TIM5;
#ifdef NVIC_TIM5_IRQ
    static constexpr uint8_t nvic = NVIC_TIM5_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM5_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM5_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM5_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM5_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM5_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM5_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM5_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM5_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _05 = TimerImpl<TIM5>;
#endif // TIM5

#if defined(TIM6)
template <> struct interface<TIM6> {
    static constexpr rcc_periph_clken rcc = RCC_TIM6;
    static constexpr rcc_periph_rst rst = RST_TIM6;
#ifdef NVIC_TIM6_IRQ
    static constexpr uint8_t nvic = NVIC_TIM6_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM6_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM6_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM6_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM6_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM6_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM6_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM6_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM6_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _06 = TimerImpl<TIM6>;
#endif // TIM6

#if defined(TIM7)
template <> struct interface<TIM7> {
    static constexpr rcc_periph_clken rcc = RCC_TIM7;
    static constexpr rcc_periph_rst rst = RST_TIM7;
#ifdef NVIC_TIM7_IRQ
    static constexpr uint8_t nvic = NVIC_TIM7_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM7_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM7_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM7_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM7_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM7_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM7_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM7_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM7_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _07 = TimerImpl<TIM7>;
#endif // TIM7

#if defined(TIM8)
template <> struct interface<TIM8> {
    static constexpr rcc_periph_clken rcc = RCC_TIM8;
    static constexpr rcc_periph_rst rst = RST_TIM8;
#ifdef NVIC_TIM8_IRQ
    static constexpr uint8_t nvic = NVIC_TIM8_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM8_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM8_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM8_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM8_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM8_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM8_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM8_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM8_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _08 = TimerImpl<TIM8>;
#endif // TIM8

#if defined(TIM9)
template <> struct interface<TIM9> {
    static constexpr rcc_periph_clken rcc = RCC_TIM9;
    static constexpr rcc_periph_rst rst = RST_TIM9;
#ifdef NVIC_TIM9_IRQ
    static constexpr uint8_t nvic = NVIC_TIM9_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM9_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM9_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM9_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM9_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM9_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM9_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM9_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM9_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _09 = TimerImpl<TIM9>;
#endif // TIM9

#if defined(TIM10)
template <> struct interface<TIM10> {
    static constexpr rcc_periph_clken rcc = RCC_TIM10;
    static constexpr rcc_periph_rst rst = RST_TIM10;
#ifdef NVIC_TIM10_IRQ
    static constexpr uint8_t nvic = NVIC_TIM10_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM10_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM10_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM10_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM10_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM10_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM10_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM10_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM10_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _10 = TimerImpl<TIM10>;
#endif // TIM10

#if defined(TIM11)
template <> struct interface<TIM11> {
    static constexpr rcc_periph_clken rcc = RCC_TIM11;
    static constexpr rcc_periph_rst rst = RST_TIM11;
#ifdef NVIC_TIM11_IRQ
    static constexpr uint8_t nvic = NVIC_TIM11_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM11_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM11_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM11_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM11_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM11_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM11_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM11_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM11_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _11 = TimerImpl<TIM11>;
#endif // TIM11

#if defined(TIM12)
template <> struct interface<TIM12> {
    static constexpr rcc_periph_clken rcc = RCC_TIM12;
    static constexpr rcc_periph_rst rst = RST_TIM12;
#ifdef NVIC_TIM12_IRQ
    static constexpr uint8_t nvic = NVIC_TIM12_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM12_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM12_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM12_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM12_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM12_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM12_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM12_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM12_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _12 = TimerImpl<TIM12>;
#endif // TIM12

#if defined(TIM13)
template <> struct interface<TIM13> {
    static constexpr rcc_periph_clken rcc = RCC_TIM13;
    static constexpr rcc_periph_rst rst = RST_TIM13;
#ifdef NVIC_TIM13_IRQ
    static constexpr uint8_t nvic = NVIC_TIM13_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM13_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM13_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM13_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM13_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM13_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM13_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM13_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM13_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _13 = TimerImpl<TIM13>;
#endif // TIM13

#if defined(TIM14)
template <> struct interface<TIM14> {
    static constexpr rcc_periph_clken rcc = RCC_TIM14;
    static constexpr rcc_periph_rst rst = RST_TIM14;
#ifdef NVIC_TIM14_IRQ
    static constexpr uint8_t nvic = NVIC_TIM14_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM14_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM14_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM14_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM14_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM14_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM14_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM14_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM14_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _14 = TimerImpl<TIM14>;
#endif // TIM14

#if defined(TIM15)
template <> struct interface<TIM15> {
    static constexpr rcc_periph_clken rcc = RCC_TIM15;
    static constexpr rcc_periph_rst rst = RST_TIM15;
#ifdef NVIC_TIM15_IRQ
    static constexpr uint8_t nvic = NVIC_TIM15_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM15_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM15_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM15_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM15_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM15_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM15_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM15_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM15_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _15 = TimerImpl<TIM15>;
#endif // TIM15

#if defined(TIM16)
template <> struct interface<TIM16> {
    static constexpr rcc_periph_clken rcc = RCC_TIM16;
    static constexpr rcc_periph_rst rst = RST_TIM16;
#ifdef NVIC_TIM16_IRQ
    static constexpr uint8_t nvic = NVIC_TIM16_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM16_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM16_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM16_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM16_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM16_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM16_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM16_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM16_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _16 = TimerImpl<TIM16>;
#endif // TIM16

#if defined(TIM17)
template <> struct interface<TIM17> {
    static constexpr rcc_periph_clken rcc = RCC_TIM17;
    static constexpr rcc_periph_rst rst = RST_TIM17;
#ifdef NVIC_TIM17_IRQ
    static constexpr uint8_t nvic = NVIC_TIM17_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM17_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM17_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM17_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM17_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM17_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM17_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM17_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM17_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _17 = TimerImpl<TIM17>;
#endif // TIM17

#if defined(TIM18)
template <> struct interface<TIM18> {
    static constexpr rcc_periph_clken rcc = RCC_TIM18;
    static constexpr rcc_periph_rst rst = RST_TIM18;
#ifdef NVIC_TIM18_IRQ
    static constexpr uint8_t nvic = NVIC_TIM18_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM18_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM18_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM18_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM18_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM18_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM18_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM18_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM18_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _18 = TimerImpl<TIM18>;
#endif // TIM18

#if defined(TIM19)
template <> struct interface<TIM19> {
    static constexpr rcc_periph_clken rcc = RCC_TIM19;
    static constexpr rcc_periph_rst rst = RST_TIM19;
#ifdef NVIC_TIM19_IRQ
    static constexpr uint8_t nvic = NVIC_TIM19_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM19_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM19_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM19_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM19_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM19_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM19_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM19_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM19_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _19 = TimerImpl<TIM19>;
#endif // TIM19

#if defined(TIM20)
template <> struct interface<TIM20> {
    static constexpr rcc_periph_clken rcc = RCC_TIM20;
    static constexpr rcc_periph_rst rst = RST_TIM20;
#ifdef NVIC_TIM20_IRQ
    static constexpr uint8_t nvic = NVIC_TIM20_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM20_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM20_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM20_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM20_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM20_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM20_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM20_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM20_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _20 = TimerImpl<TIM20>;
#endif // TIM20

#if defined(TIM21)
template <> struct interface<TIM21> {
    static constexpr rcc_periph_clken rcc = RCC_TIM21;
    static constexpr rcc_periph_rst rst = RST_TIM21;
#ifdef NVIC_TIM21_IRQ
    static constexpr uint8_t nvic = NVIC_TIM21_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM21_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM21_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM21_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM21_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM21_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM21_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM21_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM21_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _21 = TimerImpl<TIM21>;
#endif // TIM21

#if defined(TIM22)
template <> struct interface<TIM22> {
    static constexpr rcc_periph_clken rcc = RCC_TIM22;
    static constexpr rcc_periph_rst rst = RST_TIM22;
#ifdef NVIC_TIM22_IRQ
    static constexpr uint8_t nvic = NVIC_TIM22_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM22_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM22_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM22_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM22_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM22_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM22_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM22_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM22_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
};
using _22 = TimerImpl<TIM22>;
#endif // TIM22
} // namespace hal::timer
