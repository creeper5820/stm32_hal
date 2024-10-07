#pragma once

#include "interface.hh"
#include <cstddef>

#ifdef HAL_UART_MODULE_ENABLED

namespace hal {

template <UART_HandleTypeDef* _handle>
class Serial {
public:
    using Callback = void (*)(UART_HandleTypeDef*, uint16_t);

    void set_callback(Callback callback) {
        callback_ = callback;
    }

    // Send
    template <Mode mode>
    static inline Status send(uint8_t bytes[], uint16_t size, uint32_t timeout = 50) {
        if (mode == Mode::Normal)
            return static_cast<Status>(HAL_UART_Transmit(_handle, bytes, size, timeout));
        else if (mode == Mode::It)
            return static_cast<Status>(HAL_UART_Transmit_IT(_handle, bytes, size));
        else if (mode == Mode::Dma)
            return static_cast<Status>(HAL_UART_Transmit_DMA(_handle, bytes, size));
    }
    template <Mode mode, size_t length>
    static inline Status send(const uint8_t (&bytes)[length], uint32_t timeout = 50) {
        return send<mode>(bytes, length, timeout);
    }

    // Receive
    template <Mode mode>
    static inline Status receive(uint8_t bytes[], uint16_t size, uint32_t timeout = 50) {
        if (mode == Mode::Normal)
            return static_cast<Status>(HAL_UART_Receive(_handle, bytes, size, timeout));
        else if (mode == Mode::It)
            return static_cast<Status>(HAL_UART_Receive_IT(_handle, bytes, size));
        else if (mode == Mode::Dma)
            return static_cast<Status>(HAL_UART_Receive_DMA(_handle, bytes, size));
    }
    template <Mode mode, size_t length>
    static inline Status receive(uint8_t (&bytes)[length], uint32_t timeout = 50) {
        return receive<mode>(bytes, length, timeout);
    }

    // Receive with idle
    template <Mode mode>
    static inline Status receive_idle(uint8_t bytes[], uint16_t size) {
        if (mode == Mode::It)
            return static_cast<Status>(HAL_UARTEx_ReceiveToIdle_IT(_handle, bytes, size));
        else if (mode == Mode::Dma)
            return static_cast<Status>(HAL_UARTEx_ReceiveToIdle_DMA(_handle, bytes, size));
    }
    template <Mode mode, size_t length>
    static inline Status receive_idle(uint8_t (&bytes)[length]) {
        return receive_idle<mode>(bytes, length);
    }

    static inline Status receive_idle(uint8_t bytes[], uint16_t& receive_size,
        uint16_t max_size, uint32_t timeout = 50) {
        return static_cast<Status>(HAL_UARTEx_ReceiveToIdle(
            _handle, bytes, max_size, &receive_size, timeout));
    }
    template <size_t length>
    static inline Status receive_idle(uint8_t (&bytes)[length],
        uint16_t& receive_size, uint32_t timeout = 50) {
        return receive_idle(bytes, receive_size, length, timeout);
    }

    // Callback
    static inline void callback(UART_HandleTypeDef* huart, uint16_t size) {
        if (_handle != huart)
            return;
        callback_(huart, size);
    }

    template <Mode mode>
    static inline void hello_world() {
        send<mode>((uint8_t*)&"Hello World!\n", 50);
    }

private:
    static inline Callback callback_ { [](UART_HandleTypeDef*, uint16_t) { } };
};
}

#endif