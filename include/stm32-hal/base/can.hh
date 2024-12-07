#pragma once

#ifdef CAN_RxHeaderTypeDef

#include "can.h"

#include <cassert>
#include <cstdint>

namespace base {
class CanServer {
public:
    using Callback = void (*)(CAN_RxHeaderTypeDef&, const uint8_t*);

public:
    CanServer(CAN_HandleTypeDef* hcan)
        : hcan_(hcan) {
        // default filter config
        filter_.FilterActivation = CAN_FILTER_ENABLE;
        filter_.FilterFIFOAssignment = CAN_FILTER_FIFO0;
        filter_.FilterMode = CAN_FILTERMODE_IDMASK;
        filter_.FilterScale = CAN_FILTERSCALE_32BIT;
        filter_.FilterIdHigh = 0x00;
        filter_.FilterIdLow = 0x00;
        filter_.FilterMaskIdHigh = 0x00;
        filter_.FilterMaskIdLow = 0x00;
        filter_.FilterBank = 0;
        filter_.SlaveStartFilterBank = 0;

        // default handle function
        callback_ = [](CAN_RxHeaderTypeDef& header, const uint8_t data[8]) -> void {
            (void)header;
            (void)data;
        };
    }

    void set_filter(const CAN_FilterTypeDef& filter) { filter_ = filter; }

    void set_callback(const Callback& callback) { callback_ = callback; }

    void init(const uint32_t& type_active = CAN_IT_RX_FIFO0_MSG_PENDING) {
        assert(HAL_CAN_ConfigFilter(hcan_, &filter_) == HAL_OK);
        assert(HAL_CAN_Start(hcan_) == HAL_OK);
        assert(HAL_CAN_ActivateNotification(hcan_, type_active) == HAL_OK);
    }

    void start() { HAL_CAN_Start(hcan_); }

    void stop() { HAL_CAN_Stop(hcan_); }

    void callback(CAN_HandleTypeDef* hcan) {
        if (hcan != hcan_) return;

        uint8_t data[8];
        CAN_RxHeaderTypeDef header;
        HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &header, data);
        callback_(header, data);
    }

private:
    CAN_HandleTypeDef* hcan_;
    CAN_FilterTypeDef filter_;
    Callback callback_;
};

class CanClient {
public:
    using HeaderType = CAN_TxHeaderTypeDef;

    CanClient(CAN_HandleTypeDef* hcan)
        : hcan_(hcan) {
        // @brief default header of transmit
        header_tx_.StdId = 0x200;
        header_tx_.IDE = CAN_ID_STD;
        header_tx_.RTR = CAN_RTR_DATA;
        header_tx_.DLC = 8;
        header_tx_.TransmitGlobalTime = DISABLE;
    }

    void set_header_tx(const CAN_TxHeaderTypeDef& header_tx) { header_tx_ = header_tx; }

    void send(const uint8_t data[8]) {
        uint32_t mail;
        HAL_CAN_AddTxMessage(hcan_, &header_tx_, (uint8_t*)data, &mail);
    }

private:
    CAN_HandleTypeDef* hcan_;
    CAN_TxHeaderTypeDef header_tx_;
};
} // namespace base

#endif