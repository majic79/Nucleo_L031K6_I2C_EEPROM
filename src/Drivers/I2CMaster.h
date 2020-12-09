#pragma once

#include "system.h"
#include "Drivers/Device.h"
#include "Drivers/UART.h"

#define I2C_CLK_ENABLE()  __I2C1_CLK_ENABLE()
#define I2C_CLK_DISABLE()  __I2C1_CLK_DISABLE()

#define I2C_PINS    (GPIO_PIN_9 | GPIO_PIN_10)
#define I2C_PORT    GPIOA
#define I2C_Alternate   GPIO_AF1_I2C1

class I2CMaster : public Device {
    private:
        I2C_HandleTypeDef hI2C;

    public:
        I2CMaster();
        ~I2CMaster();
        virtual void InitDevice();
        HAL_StatusTypeDef Write(uint16_t deviceAddress, uint16_t memAddress, uint8_t* buf, uint16_t size, uint32_t timeout);
        HAL_StatusTypeDef Read(uint16_t deviceAddress, uint16_t memAddress, uint8_t* buf, uint16_t size, uint32_t timeout);
        void ReportError(UART out);
};
