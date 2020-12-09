#include "system.h"

#include "Drivers/UART.h"

static UART_HandleTypeDef *hpUART2;

void UART2_IRQHandler(void) {
    HAL_UART_IRQHandler(hpUART2);
}

UART::UART(uint32_t baudRate) {
    // Base Constructor
    hpUART2 = &hUART;
    baud = baudRate;
}

UART::~UART() {
    USARTx_CLK_DISABLE();
}

void UART::InitDevice() {
    GPIO_InitTypeDef  GPIO_InitStruct;

    USARTx_CLK_ENABLE();
    
    GPIO_InitStruct.Pin       = USARTx_TX_RX_PINS;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = USARTx_TX_RX_AF;

    HAL_GPIO_Init(USARTx_TX_RX_GPIO, &GPIO_InitStruct);

    hUART.Instance          = USARTx;

    hUART.Init.BaudRate     = baud;
    hUART.Init.WordLength   = UART_WORDLENGTH_8B;
    hUART.Init.StopBits     = UART_STOPBITS_1;
    hUART.Init.Parity       = UART_PARITY_NONE;
    hUART.Init.HwFlowCtl    = UART_HWCONTROL_RTS_CTS;
    hUART.Init.Mode         = UART_MODE_TX_RX;
    hUART.Init.OverSampling = UART_OVERSAMPLING_16;

    if(HAL_UART_Init(&hUART) != HAL_OK) {
        while(1){}
    }
}

HAL_StatusTypeDef UART::putc(char c) {
    return HAL_UART_Transmit(&hUART, (uint8_t*)(&c), 1, 1000);
}

HAL_StatusTypeDef UART::puts(const char* s, uint8_t l) {
    HAL_StatusTypeDef r = HAL_StatusTypeDef::HAL_OK;
    for(uint8_t a=0;a<l && s[a]!=0;a++)
        r = putc(s[a]);
    return r;
}

void UART::puthex(uint8_t v)
{
    const char hexCode[17] = "0123456789ABCDEF";
    putc(hexCode[((v & 0xF0) >> 4)]);
    putc(hexCode[(v & 0x0F)]);
}

void UART::puthex(uint16_t v)
{
    puthex((uint8_t)((v & 0xFF00) >> 8));
    puthex((uint8_t)((v & 0x00FF)));
}

void UART::puthex(uint32_t v)
{
    puthex((uint16_t)((v & 0xFFFF0000) >> 16));
    puthex((uint16_t)((v & 0x0000FFFF)));
}
