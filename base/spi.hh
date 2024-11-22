#pragma once

#include "spi.h"

// (#) TX/RX processes are HAL_SPI_TransmitReceive(), HAL_SPI_TransmitReceive_IT() and
// HAL_SPI_TransmitReceive_DMA()
// (#) RX processes are HAL_SPI_Receive(), HAL_SPI_Receive_IT() and HAL_SPI_Receive_DMA()
// (#) TX processes are HAL_SPI_Transmit(), HAL_SPI_Transmit_IT() and HAL_SPI_Transmit_DMA()

namespace base {
enum SpiTransmitType { SPI_TRANSMIT_TYPE, SPI_TRANSMIT_IT_TYPE, SPI_TRANSMIT_DMA_TYPE };

enum SpiReceiveType { SPI_RECEIVE_TYPE, SPI_RECEIVE_IT_TYPE, SPI_RECEIVE_DMA_TYPE };

enum SpiTransmitAndReceiveType {
    SPI_TRANSMIT_RECEIVE_TYPE,
    SPI_TRANSMIT_RECEIVE_IT_TYPE,
    SPI_TRANSMIT_RECEIVE_DMA_TYPE
};

class SPI {
private:
    SPI_HandleTypeDef* spi_;

public:
    SPI(SPI_HandleTypeDef* spi)
        : spi_(spi) { }

    /**
     * @brief spi transmit function
     *
     * @param type TRANSMIT_TYPE  TRANSMIT_IT_TYPE  TRANSMIT_DMA_TYPE
     * @param data
     * @param size
     * @param timeout
     */
    void transmit(SpiTransmitType type, uint8_t* data, uint16_t size, uint32_t timeout = 0xffff) {
        switch (type) {
        case SPI_TRANSMIT_TYPE: {
            HAL_SPI_Transmit(spi_, data, size, timeout);
            break;
        }
        case SPI_TRANSMIT_IT_TYPE: {
            HAL_SPI_Transmit_IT(spi_, data, size);
            break;
        }
        case SPI_TRANSMIT_DMA_TYPE: {
            HAL_SPI_Transmit_DMA(spi_, data, size);
            break;
        }
        }
    }

    /**
     * @brief spi receive function
     *
     * @param type
     * @param data
     * @param size
     * @param timout
     */
    void receive(SpiReceiveType type, uint8_t* data, uint16_t size, uint32_t timout = 0xffff) {
        switch (type) {
        case SPI_RECEIVE_TYPE: {
            break;
        }
        case SPI_RECEIVE_IT_TYPE: {
            break;
        }
        case SPI_RECEIVE_DMA_TYPE: {
            break;
        }
        }
    }

    /**
     * @brief spi transmit and receive function
     *
     * @param type
     * @param data_tx
     * @param data_rx
     * @param size
     * @param timout
     */
    void transmit_receive(SpiTransmitAndReceiveType type, uint8_t* data_tx, uint8_t* data_rx,
        uint16_t size, uint32_t timout = 0xffff) { }
};
}