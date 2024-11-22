#pragma once

#include "interface.hh"
#include <concepts>
#include <cstddef>

#ifdef HAL_UART_MODULE_ENABLED

namespace hal {

using UartHandler = UART_HandleTypeDef*;

template <UartHandler _handle> class Serial {
public:
    using SerialCallback = void (*)(UartHandler, uint16_t);
    static inline void set_callback(SerialCallback callback) { callback_ = callback; }

    // Send
    template <Mode mode>
    static inline Status send(uint8_t bytes[], uint16_t size, uint32_t timeout = 50) {
        if constexpr (mode == Mode::Normal)
            return static_cast<Status>(HAL_UART_Transmit(_handle, bytes, size, timeout));
        else if constexpr (mode == Mode::It)
            return static_cast<Status>(HAL_UART_Transmit_IT(_handle, bytes, size));
        else if constexpr (mode == Mode::Dma)
            return static_cast<Status>(HAL_UART_Transmit_DMA(_handle, bytes, size));
    }
    template <Mode mode, size_t length>
    static inline Status send(const uint8_t (&bytes)[length], uint32_t timeout = 50) {
        return send<mode>(bytes, length, timeout);
    }

    // Receive
    template <Mode mode>
    static inline Status receive(uint8_t bytes[], uint16_t size, uint32_t timeout = 50) {
        if constexpr (mode == Mode::Normal)
            return static_cast<Status>(HAL_UART_Receive(_handle, bytes, size, timeout));
        else if constexpr (mode == Mode::It)
            return static_cast<Status>(HAL_UART_Receive_IT(_handle, bytes, size));
        else if constexpr (mode == Mode::Dma)
            return static_cast<Status>(HAL_UART_Receive_DMA(_handle, bytes, size));
    }
    template <Mode mode, size_t length>
    static inline Status receive(uint8_t (&bytes)[length], uint32_t timeout = 50) {
        return receive<mode>(bytes, length, timeout);
    }

    // Receive with idle
    template <Mode mode> static inline Status receive_idle(uint8_t bytes[], uint16_t size) {
        if constexpr (mode == Mode::It)
            return static_cast<Status>(HAL_UARTEx_ReceiveToIdle_IT(_handle, bytes, size));
        else if constexpr (mode == Mode::Dma)
            return static_cast<Status>(HAL_UARTEx_ReceiveToIdle_DMA(_handle, bytes, size));
    }
    template <Mode mode, size_t length>
    static inline Status receive_idle(uint8_t (&bytes)[length]) {
        return receive_idle<mode>(bytes, length);
    }

    static inline Status receive_idle(
        uint8_t bytes[], uint16_t& receive_size, uint16_t max_size, uint32_t timeout = 50) {
        return static_cast<Status>(
            HAL_UARTEx_ReceiveToIdle(_handle, bytes, max_size, &receive_size, timeout));
    }
    template <size_t length>
    static inline Status receive_idle(
        uint8_t (&bytes)[length], uint16_t& receive_size, uint32_t timeout = 50) {
        return receive_idle(bytes, receive_size, length, timeout);
    }

    // Callback
    static inline void callback(UartHandler huart, uint16_t size) {
        if (_handle != huart) return;
        callback_(huart, size);
    }

    template <Mode mode> static inline void hello_world() {
        send<mode>((uint8_t*)&"Hello World!\n", 50);
    }

private:
    static inline SerialCallback callback_ { [](UartHandler, uint16_t) { } };
};

namespace internal {
    template <typename Handler>
    concept SerialStaticCallableConcept = requires(Handler, UartHandler huart, uint16_t size) {
        { Handler::callback(huart, size) } -> std::same_as<void>;
    };
    template <typename Handler>
    concept SerialNormalCallableConcept
        = requires(Handler handler, UartHandler huart, uint16_t size) {
              { handler.callback(huart, size) } -> std::same_as<void>;
          };
    template <typename Handler>
    concept SerialDirectCallableConcept
        = requires(Handler handler, UartHandler huart, uint16_t size) {
              { handler(huart, size) } -> std::same_as<void>;
          };
    template <typename Handlers>
    concept SerialDirectCallableNoArgsConcept = requires(Handlers handler) {
        { handler() } -> std::same_as<void>;
    };

    void call_serial_callback(
        UartHandler huart, uint16_t size, SerialStaticCallableConcept auto const& handler) {
        handler.callback(huart, size);
    }
    void call_serial_callback(
        UartHandler huart, uint16_t size, SerialNormalCallableConcept auto&& handlers) {
        handlers.callback(huart, size);
    }
    void call_serial_callback(
        UartHandler huart, uint16_t size, SerialDirectCallableConcept auto&& handlers) {
        handlers(huart, size);
    }
    void call_serial_callback(
        UartHandler, uint16_t, SerialDirectCallableNoArgsConcept auto&& handlers) {
        handlers();
    }

    void execute_serial_callbacks(UartHandler huart, uint16_t size, auto&&... handlers) {
        (call_serial_callback(huart, size, std::forward<decltype(handlers)>(handlers)), ...);
    }
}

#define GENERATE_UART_RX_EVENT_CALLBACK(...)                                                       \
    void HAL_UARTEx_RxEventCallback(UartHandler huart, uint16_t size) {                            \
        hal::internal::execute_serial_callbacks(huart, size, __VA_ARGS__);                         \
    }
#define GENERATE_UART_RX_COMPLETE_CALLBACK(...)                                                    \
    void HAL_UARTEx_RxCpltCallback(UartHandler huart) {                                            \
        hal::internal::execute_serial_callbacks(huart, 0, __VA_ARGS__);                            \
    }

}

#endif