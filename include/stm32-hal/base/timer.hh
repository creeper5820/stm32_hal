#pragma once

#include "timer-interfaces.hh"

namespace hal::timer {
template <uint32_t _peripheral> class TimerImpl {
private:
    template <uint32_t _division, uint32_t _alignment> struct direction_ {
        static void up() {
            rcc_periph_clock_enable(interface<_peripheral>::rcc);
            timer_set_mode(_peripheral, _division, _alignment, TIM_CR1_DIR_UP);
        }
        static void down() {
            rcc_periph_clock_enable(interface<_peripheral>::rcc);
            timer_set_mode(_peripheral, _division, _alignment, TIM_CR1_DIR_DOWN);
        }
    };
    template <uint32_t _d> struct alignment_ {
        using edge = direction_<_d, TIM_CR1_CMS_EDGE>;
        using center1 = direction_<_d, TIM_CR1_CMS_CENTER_1>;
        using center2 = direction_<_d, TIM_CR1_CMS_CENTER_2>;
        using center3 = direction_<_d, TIM_CR1_CMS_CENTER_3>;
    };

    template <uint16_t _irq, uint8_t _nvic> struct irq_ {
        static void disable() { timer_disable_irq(_peripheral, _irq); }
        static void clear() { timer_clear_flag(_peripheral, _irq); }
        static void set_priority(uint8_t priority) { nvic_set_priority(_nvic, priority); }
        static void enable_without_nvic() { timer_enable_irq(_peripheral, _irq); }
        static void enable_with_nvic() {
            timer_enable_irq(_peripheral, _irq);
            if constexpr (_nvic != NVIC_IRQ_COUNT) nvic_enable_irq(_nvic);
            if constexpr (interface<_peripheral>::nvic != NVIC_IRQ_COUNT)
                nvic_enable_irq(interface<_peripheral>::nvic);
        }
        static void enable_with_nvic(uint8_t priority) {
            constexpr auto nvic = interface<_peripheral>::nvic;
            timer_enable_irq(_peripheral, _irq);
            if constexpr (_nvic != NVIC_IRQ_COUNT)
                nvic_set_priority(_nvic, priority), nvic_enable_irq(_nvic);
            if constexpr (nvic != NVIC_IRQ_COUNT)
                nvic_set_priority(nvic, priority), nvic_enable_irq(nvic);
        }
    };

    template <uint16_t _flag> struct flag_ {
        static bool get() { return timer_get_flag(_peripheral, _flag); }
        static void clear() { timer_clear_flag(_peripheral, _flag); }
    };

public:
    struct setup {
        using mul1 = alignment_<TIM_CR1_CKD_CK_INT>;
        using mul2 = alignment_<TIM_CR1_CKD_CK_INT_MUL_2>;
        using mul4 = alignment_<TIM_CR1_CKD_CK_INT_MUL_4>;

        struct templates {
            static void timer(uint32_t prescaler, uint32_t period) {
                reset();
                setup::mul1::edge::up();
                load::prescaler(prescaler);
                load::period(period);
                counter::enable();
                irq::up::clear();
                irq::up::enable_with_nvic();
            }
        };
    };
    struct irq {
        struct dma {
            using trg = irq_<TIM_DIER_TDE, interface<_peripheral>::nvic_trg_com>;
            using cc = irq_<TIM_DIER_COMDE, interface<_peripheral>::nvic_trg_com>;
            using cc4 = irq_<TIM_DIER_CC4DE, interface<_peripheral>::nvic_trg_com>;
            using cc3 = irq_<TIM_DIER_CC3DE, interface<_peripheral>::nvic_trg_com>;
            using cc2 = irq_<TIM_DIER_CC2DE, interface<_peripheral>::nvic_trg_com>;
            using cc1 = irq_<TIM_DIER_CC1DE, interface<_peripheral>::nvic_trg_com>;
            using up = irq_<TIM_DIER_UIE, interface<_peripheral>::nvic_up>;
        };
        using brk = irq_<TIM_DIER_BIE, interface<_peripheral>::nvic_brk>;
        using trg = irq_<TIM_DIER_TIE, interface<_peripheral>::nvic_trg_com>;
        using cc = irq_<TIM_DIER_COMIE, interface<_peripheral>::nvic_trg_com>;
        using cc4 = irq_<TIM_DIER_CC4IE, interface<_peripheral>::nvic_trg_com>;
        using cc3 = irq_<TIM_DIER_CC3IE, interface<_peripheral>::nvic_trg_com>;
        using cc2 = irq_<TIM_DIER_CC2IE, interface<_peripheral>::nvic_trg_com>;
        using cc1 = irq_<TIM_DIER_CC1IE, interface<_peripheral>::nvic_trg_com>;
        using up = irq_<TIM_DIER_UIE, interface<_peripheral>::nvic_up>;
    };
    struct flag {
        struct overcapture {
            using cc4 = flag_<TIM_SR_CC4OF>;
            using cc3 = flag_<TIM_SR_CC3OF>;
            using cc2 = flag_<TIM_SR_CC2OF>;
            using cc1 = flag_<TIM_SR_CC1OF>;
        };
        struct irq {
            using _break = flag_<TIM_SR_BIF>;
            using trigger = flag_<TIM_SR_TIF>;
            using com = flag_<TIM_SR_COMIF>;
            using cc4 = flag_<TIM_SR_CC4IF>;
            using cc3 = flag_<TIM_SR_CC3IF>;
            using cc2 = flag_<TIM_SR_CC2IF>;
            using cc1 = flag_<TIM_SR_CC1IF>;
            using update = flag_<TIM_SR_UIF>;
        };
        static void clear_all() {
            overcapture::cc4::clear(), overcapture::cc3::clear();
            overcapture::cc2::clear(), overcapture::cc1::clear();
            irq::cc4::clear(), irq::cc3::clear(), irq::cc2::clear(), irq::cc1::clear();
            irq::_break::clear(), irq::trigger::clear(), irq::update::clear();
            irq::com::clear();
        }
    };
    struct load {
        static void prescaler(uint32_t value) { timer_set_prescaler(_peripheral, value); }
        static void period(uint32_t value) { timer_set_period(_peripheral, value); }
    };
    struct preload {
        static void enable() { timer_enable_preload(_peripheral); }
        static void disable() { timer_disable_preload(_peripheral); }
    };
    struct counter {
        static void enable() { timer_enable_counter(_peripheral); }
        static void disable() { timer_disable_counter(_peripheral); }
    };
    struct count_mode {
        static void continuous() { timer_continuous_mode(_peripheral); }
        static void one_shot() { timer_one_shot_mode(_peripheral); }
    };

    /// @todo
    /// using gpio = pwm::channel<index>;

    static inline void reset() { rcc_periph_reset_pulse(interface<_peripheral>::rst); }
    static inline constexpr uint32_t peripheral() { return _peripheral; }

    struct attribute {
        static constexpr uint32_t peripheral = _peripheral;
        struct timer_token { };
    };
};

template <typename timer>
concept timer_concept = requires { typename timer::attribute::timer_token; };

}
