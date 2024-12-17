#!/usr/bin/env python3
import os

header = """#pragma once

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
"""

footer = """} // namespace hal::timer
"""

timer_template = """
#if defined({peripheral_base})
using _{index:02d} = Timer<TIM{index}>;
template <> constexpr rcc_periph_clken timer_rcc<TIM{index}>() {{ return RCC_TIM{index}; }}
template <> constexpr rcc_periph_rst timer_rst<TIM{index}>() {{ return RST_TIM{index}; }}
template <> constexpr uint8_t timer_nvic<TIM{index}>() {{
#ifdef NVIC_TIM{index}_IRQ
    return NVIC_TIM{index}_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}}
template <> constexpr uint8_t timer_nvic_brk<TIM{index}>() {{
#ifdef NVIC_TIM{index}_BRK_IRQ
    return NVIC_TIM{index}_BRK_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}}
template <> constexpr uint8_t timer_nvic_up<TIM{index}>() {{
#ifdef NVIC_TIM{index}_UP_IRQ
    return NVIC_TIM{index}_UP_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}}
template <> constexpr uint8_t timer_nvic_trg_com<TIM{index}>() {{
#ifdef NVIC_TIM{index}_TRG_COM_IRQ
    return NVIC_TIM{index}_TRG_COM_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}}
template <> constexpr uint8_t timer_nvic_cc<TIM{index}>() {{
#ifdef NVIC_TIM{index}_CC_IRQ
    return NVIC_TIM{index}_CC_IRQ;
#else
    return NVIC_IRQ_COUNT;
#endif
}}
#endif // {peripheral_base}
"""

timers = [
    "TIM1_BASE",
    "TIM2_BASE",
    "TIM3_BASE",
    "TIM4_BASE",
    "TIM5_BASE",
    "TIM6_BASE",
    "TIM7_BASE",
    "TIM8_BASE",
    "TIM9_BASE",
    "TIM10_BASE",
    "TIM11_BASE",
    "TIM12_BASE",
    "TIM13_BASE",
    "TIM14_BASE",
    "TIM15_BASE",
    "TIM16_BASE",
    "TIM17_BASE",
    "TIM21_BASE",
    "TIM22_BASE",
]

current_file_path = os.path.abspath(__file__)
current_dir_path = os.path.dirname(current_file_path)
output_file_path = os.path.join(current_dir_path, "timer-interfaces.hh")

with open(output_file_path, "w") as f:
    f.write(header)

    for i, base in enumerate(timers, start=1):
        peripheral_base = base.replace("_BASE", "")
        f.write(
            timer_template.format(index=i, peripheral_base=peripheral_base, base=base)
        )

    f.write(footer)
