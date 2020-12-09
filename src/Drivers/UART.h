#pragma once

#include "system.h"

#include "Drivers/Device.h"

#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE()
#define USARTx_CLK_DISABLE()             __HAL_RCC_USART2_CLK_DISABLE()
#define USARTx_TX_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_RX_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

#define USARTx_TX_RX_PINS       (GPIO_PIN_2 | GPIO_PIN_15)
#define USARTx_TX_RX_GPIO       GPIOA
#define USARTx_TX_RX_AF         GPIO_AF4_USART2

class UART : public Device{
    private:
    protected:
        UART_HandleTypeDef hUART;
        uint32_t baud;
    public:
        UART(uint32_t baud);
        ~UART();
        virtual void InitDevice();
        HAL_StatusTypeDef putc(char c);
        HAL_StatusTypeDef puts(const char* s, uint8_t l);
        void puthex(uint8_t v);
        void puthex(uint16_t v);
        void puthex(uint32_t v);
        void flush();
};

extern "C" void UART2_IRQHandler(void);