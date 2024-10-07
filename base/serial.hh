#pragma once

#include "interface.hh"

#ifdef HAL_UART_MODULE_ENABLED

namespace hal {

class Serial {
public:
    enum class Status {
        WAIT,
        READY,
    };

    enum class Mode {
        NORMAL,
        IT,
        DMA
    };

    using Callback = void (*)(UART_HandleTypeDef*, uint16_t);

public:
    Serial(UART_HandleTypeDef* huart)
        : huart_(huart) {
        callback_ = [](UART_HandleTypeDef* huart, uint16_t size) { (void)huart; (void)size ; };
    }

    void init() {
    }

    void set_callback(const Callback& callback) {
        callback_ = callback;
    }

    template <Mode mode>
    HAL_StatusTypeDef send(uint8_t* data, const uint16_t& size = 0, uint32_t timeout = 50) {
        if constexpr (mode == Mode::NORMAL)
            return HAL_UART_Transmit(huart_, data, size, timeout);
        else if constexpr (mode == Mode::IT)
            return HAL_UART_Transmit_IT(huart_, data, size);
        else if constexpr (mode == Mode::DMA)
            return HAL_UART_Transmit_DMA(huart_, data, size);
    }

    template <Mode mode>
    HAL_StatusTypeDef receive(uint8_t* data, const uint16_t& size = 0, uint32_t timeout = 50) {
        if constexpr (mode == Mode::NORMAL)
            return HAL_UART_Receive(huart_, data, size, timeout);
        else if constexpr (mode == Mode::IT)
            return HAL_UART_Receive_IT(huart_, data, size);
        else if constexpr (mode == Mode::DMA)
            return HAL_UART_Receive_DMA(huart_, data, size);
    }

    template <Mode mode>
    HAL_StatusTypeDef receive_idle(uint8_t* data, uint16_t* real_size, uint16_t size, uint32_t timeout = 50) {
        if constexpr (mode == Mode::NORMAL) {
            return HAL_UARTEx_ReceiveToIdle(huart_, data, size, real_size, timeout);
        }
    }

    template <Mode mode>
    HAL_StatusTypeDef receive_idle(uint8_t* data, uint16_t size) {
        if constexpr (mode == Mode::IT)
            return HAL_UARTEx_ReceiveToIdle_IT(huart_, data, size);
        else if constexpr (mode == Mode::DMA)
            return HAL_UARTEx_ReceiveToIdle_DMA(huart_, data, size);
    }

    void callback(UART_HandleTypeDef* huart, uint16_t size) {
        if (huart_ != huart)
            return;
        callback_(huart, size);
    }

    template <Mode mode>
    void HelloWorld() {
        send<mode>((uint8_t*)&"Hello World!\n", sizeof("Hello World!"), 50);
    }

private:
    UART_HandleTypeDef* huart_;

    Callback callback_;
};
}

#endif