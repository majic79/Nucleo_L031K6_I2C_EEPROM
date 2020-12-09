#include "Drivers/I2CMaster.h"
#include "Drivers/UART.h"

I2CMaster::I2CMaster() {
    // Default Constructor
}

I2CMaster::~I2CMaster() {
    // Default destructor
    I2C_CLK_DISABLE();
}

void I2CMaster::InitDevice() {
    GPIO_InitTypeDef  GPIO_InitStruct;

    I2C_CLK_ENABLE();
    
    GPIO_InitStruct.Pin       = I2C_PINS;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = I2C_Alternate;

    HAL_GPIO_Init(I2C_PORT, &GPIO_InitStruct);

    hI2C.Instance = I2C1;
    hI2C.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    //hI2C.Init.Timing = 0x30420F13; // 100Khz Standard mode - 16MHz master clock
    // 100kHz I2C Clock (Standard Mode)
    // 16MHz master clock
    // PRESC: 3
    // SCLL: 0x13
    // tSCLL: 5.0us
    // SCLH: 0xF
    // tSCLH: 4.0us
    // tSCL: ~10us
    // SDADEL: 0x2
    // tSDADEL: 500ns
    // SCLDEL: 0x4
    // tSCLDEL: 1250ns

    hI2C.Init.Timing = 0x10320309; // 400Khz Fast mode - 16MHz master clock
    // 100kHz I2C Clock (Standard Mode)
    // 16MHz master clock
    // PRESC: 1
    // SCLL: 0x09
    // tSCLL: 1250ns
    // SCLH: 0x3
    // tSCLH: 500ns
    // tSCL: ~2500ns
    // SDADEL: 0x2
    // tSDADEL: 250ns
    // SCLDEL: 0x3
    // tSCLDEL: 500ns

    if(HAL_I2C_Init(&hI2C) != HAL_OK) {
        while(1){}
    }
}

HAL_StatusTypeDef I2CMaster::Write(uint16_t deviceAddress, uint16_t memAddress, uint8_t* buf, uint16_t size, uint32_t timeout){
    return HAL_I2C_Mem_Write(&hI2C, deviceAddress, memAddress, I2C_MEMADD_SIZE_16BIT, buf, size, timeout);
}

HAL_StatusTypeDef I2CMaster::Read(uint16_t deviceAddress, uint16_t memAddress, uint8_t* buf, uint16_t size, uint32_t timeout){
    return HAL_I2C_Mem_Read(&hI2C, deviceAddress, memAddress, I2C_MEMADD_SIZE_16BIT, buf, size, timeout);
}

void I2CMaster::ReportError(UART out){
    const char errM[8] = "I2C E: ";
    uint32_t err = HAL_I2C_GetError(&hI2C);
    out.puts(errM, 8);
    out.puthex(err);
    out.putc('\n');
}