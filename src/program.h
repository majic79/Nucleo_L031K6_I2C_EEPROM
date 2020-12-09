#include "system.h"
#include "Drivers/DigitalPin.h"
#include "Drivers/UART.h"
#include "Drivers/I2CMaster.h"

#define LED_PIN     GPIO_PIN_3
#define LED_GPIO_PORT   GPIOB
#define LED_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

class Program {
    private:
        OutputPin userLed;
        UART debug;
        I2CMaster i2c;
    protected:
        void InitGPIO();
    public:
        Program();
        void Startup();
        void MainLoop();
        inline void Wait(uint32_t delay_ms);
};