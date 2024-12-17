#pragma once

#include "timer-interfaces.hh"

namespace hal::timer {
template <uint32_t _peripheral> class Timer {
private:
    template <uint32_t _division, uint32_t _alignment> struct direction_ {
        static void up() {
            rcc_periph_clock_enable(timer_rcc<_peripheral>());
            timer_set_mode(_peripheral, _division, _alignment, TIM_CR1_DIR_UP);
        }
        static void down() {
            rcc_periph_clock_enable(timer_rcc<_peripheral>());
            timer_set_mode(_peripheral, _division, _alignment, TIM_CR1_DIR_DOWN);
        }
    };
    template <uint32_t _d> struct alignment_ {
        using edge = direction_<_d, TIM_CR1_CMS_EDGE>;
        using center1 = direction_<_d, TIM_CR1_CMS_CENTER_1>;
        using center2 = direction_<_d, TIM_CR1_CMS_CENTER_2>;
        using center3 = direction_<_d, TIM_CR1_CMS_CENTER_3>;
        using mask = direction_<_d, TIM_CR1_CMS_MASK>;
    };

    template <uint16_t _irq, uint8_t _nvic> struct irq_ {
        static void disable() { timer_disable_irq(_peripheral, _irq); }
        static void clear() { timer_clear_flag(_peripheral, _irq); }
        static void set_priority(uint8_t priority) { nvic_set_priority(_nvic, priority); }
        static void enable_without_nvic() { timer_enable_irq(_peripheral, _irq); }
        static void enable_with_nvic() {
            timer_enable_irq(_peripheral, _irq);
            constexpr auto nvic = timer_nvic<_peripheral>();
            if constexpr (_nvic != NVIC_IRQ_COUNT) nvic_enable_irq(_nvic);
            if constexpr (nvic != NVIC_IRQ_COUNT) nvic_enable_irq(nvic);
        }
    };

    template <uint16_t _flag> struct status_ {
        static bool get() { return timer_get_flag(_peripheral, _flag); }
        static void clear() { timer_clear_flag(_peripheral, _flag); }
    };

public:
    struct irq {
        struct dma {
            using trg = irq_<TIM_DIER_TDE, timer_nvic_trg_com<_peripheral>()>;
            using cc = irq_<TIM_DIER_COMDE, timer_nvic_trg_com<_peripheral>()>;
            using cc4 = irq_<TIM_DIER_CC4DE, timer_nvic_trg_com<_peripheral>()>;
            using cc3 = irq_<TIM_DIER_CC3DE, timer_nvic_trg_com<_peripheral>()>;
            using cc2 = irq_<TIM_DIER_CC2DE, timer_nvic_trg_com<_peripheral>()>;
            using cc1 = irq_<TIM_DIER_CC1DE, timer_nvic_trg_com<_peripheral>()>;
            using up = irq_<TIM_DIER_UIE, timer_nvic_up<_peripheral>()>;
        };
        using brk = irq_<TIM_DIER_BIE, timer_nvic_brk<_peripheral>()>;
        using trg = irq_<TIM_DIER_TIE, timer_nvic_trg_com<_peripheral>()>;
        using cc = irq_<TIM_DIER_COMIE, timer_nvic_trg_com<_peripheral>()>;
        using cc4 = irq_<TIM_DIER_CC4IE, timer_nvic_trg_com<_peripheral>()>;
        using cc3 = irq_<TIM_DIER_CC3IE, timer_nvic_trg_com<_peripheral>()>;
        using cc2 = irq_<TIM_DIER_CC2IE, timer_nvic_trg_com<_peripheral>()>;
        using cc1 = irq_<TIM_DIER_CC1IE, timer_nvic_trg_com<_peripheral>()>;
        using up = irq_<TIM_DIER_UIE, timer_nvic_up<_peripheral>()>;
    };
    struct status {
        struct overcapture {
            using cc4 = status_<TIM_SR_CC4OF>;
            using cc3 = status_<TIM_SR_CC3OF>;
            using cc2 = status_<TIM_SR_CC2OF>;
            using cc1 = status_<TIM_SR_CC1OF>;
        };
        struct irq {
            using _break = status_<TIM_SR_BIF>;
            using trigger = status_<TIM_SR_TIF>;
            using com = status_<TIM_SR_COMIF>;
            using cc4 = status_<TIM_SR_CC4IF>;
            using cc3 = status_<TIM_SR_CC3IF>;
            using cc2 = status_<TIM_SR_CC2IF>;
            using cc1 = status_<TIM_SR_CC1IF>;
            using update = status_<TIM_SR_UIF>;
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

    struct setup {
        using mul1 = alignment_<TIM_CR1_CKD_CK_INT>;
        using mul2 = alignment_<TIM_CR1_CKD_CK_INT_MUL_2>;
        using mul4 = alignment_<TIM_CR1_CKD_CK_INT_MUL_4>;
        using mask = alignment_<TIM_CR1_CKD_CK_INT_MASK>;

        struct templates {
            using instance = Timer<_peripheral>;
            static inline void timer(uint32_t prescaler, uint32_t period) {
                instance::reset();
                instance::setup::mul1::edge::up();
                instance::load::prescaler(prescaler);
                instance::load::period(period);
                instance::counter::enable();
                instance::irq::up::clear();
                instance::irq::up::enable_with_nvic();
            }
        };
    };

    /// @todo
    /// using gpio = pwm::channel<index>;

    static inline void reset() { rcc_periph_reset_pulse(timer_rst<_peripheral>()); }
    static inline constexpr uint32_t peripheral() { return _peripheral; }

    struct timer_token { };
};

template <typename T>
concept timer_concept = requires { typename T::timer_token; };
}
