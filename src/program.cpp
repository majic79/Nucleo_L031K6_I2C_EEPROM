#include "system.h"
#include "program.h"

#define BUFSIZE 16
// #define MEMSIZE (BUFSIZE*512)
#define MEMSIZE (BUFSIZE*2)

#define EEPROM_ADDR (0x50 << 1)

#define MONITOR_BAUD 115200

Program::Program()
    : userLed(LED_GPIO_PORT, LED_PIN), debug(MONITOR_BAUD), i2c()
    
{
    // Any other construction
}

void Program::InitGPIO() {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
}

void Program::Startup() {
    InitGPIO();
    i2c.InitDevice();
    debug.InitDevice();
    userLed.InitDevice();
}

void Program::MainLoop(){
    // Cycle pin state
    uint8_t rbuf[BUFSIZE];
    HAL_StatusTypeDef r;
    Wait(2000);
    for(uint16_t b = 0; b < MEMSIZE; b+=BUFSIZE)
    {
        userLed.Toggle();
        r = i2c.Read(EEPROM_ADDR, b, rbuf, 16, HAL_MAX_DELAY);
        if(r!=HAL_OK) {
            i2c.ReportError(debug);
            break;
        }
        debug.puthex(b);
        debug.putc(' '); 
        for(uint8_t a = 0; a < BUFSIZE; a++)
        {
            debug.puthex(rbuf[a]);
            debug.putc(' '); 
        }
        debug.putc('\n');
    }

    while(1) {
        userLed.Toggle();
        Wait(500);
    }
}

void Program::Wait(uint32_t delay_ms)
{
    HAL_Delay(delay_ms);
}
