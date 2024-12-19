#!/usr/bin/env python3
import os

header = """#pragma once

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

namespace hal::timer {
template <uint32_t _peripheral> class TimerImpl;
template <uint32_t _peripheral> struct interface;
"""

footer = """} // namespace hal::timer
"""

timer_template = """
#if defined({peripheral_base})
template <> struct interface<TIM{index}> {{
    static constexpr rcc_periph_clken rcc = RCC_TIM{index};
    static constexpr rcc_periph_rst rst = RST_TIM{index};
#ifdef NVIC_TIM{index}_IRQ
    static constexpr uint8_t nvic = NVIC_TIM{index}_IRQ;
#else
    static constexpr uint8_t nvic = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM{index}_BRK_IRQ
    static constexpr uint8_t nvic_brk = NVIC_TIM{index}_BRK_IRQ;
#else
    static constexpr uint8_t nvic_brk = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM{index}_UP_IRQ
    static constexpr uint8_t nvic_up = NVIC_TIM{index}_UP_IRQ;
#else
    static constexpr uint8_t nvic_up = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM{index}_TRG_COM_IRQ
    static constexpr uint8_t nvic_trg_com = NVIC_TIM{index}_TRG_COM_IRQ;
#else
    static constexpr uint8_t nvic_trg_com = NVIC_IRQ_COUNT;
#endif
#ifdef NVIC_TIM{index}_CC_IRQ
    static constexpr uint8_t nvic_cc = NVIC_TIM{index}_CC_IRQ;
#else
    static constexpr uint8_t nvic_cc = NVIC_IRQ_COUNT;
#endif
}};
using _{index:02d} = TimerImpl<TIM{index}>;
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
    "TIM18_BASE",
    "TIM19_BASE",
    "TIM20_BASE",
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
