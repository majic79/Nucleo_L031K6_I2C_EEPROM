#include "system.h"
#include "Drivers/DigitalPin.h"


// Base DigitalPin
DigitalPin::DigitalPin(GPIO_TypeDef *gpioPort, uint8_t pin) {
    // Base Constructor
    gpiox = gpioPort;
    pin_number = pin;
}

DigitalPin::~DigitalPin() {
    // Base Destructor
}

// OutputPin

OutputPin::OutputPin(GPIO_TypeDef *gpioPort, uint8_t pin) : DigitalPin(gpioPort, pin)
{
    // Constructor
}

void OutputPin::InitDevice() {
    GPIO_InitTypeDef GPIO_Init;
    GPIO_Init.Pin = pin_number;
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(gpiox, &GPIO_Init);
}

OutputPin& OutputPin::operator =(GPIO_PinState pinState) {
    HAL_GPIO_WritePin(gpiox, pin_number, pinState);
    return (*this);
}

void OutputPin::Toggle() {
    HAL_GPIO_TogglePin(gpiox, pin_number);
}
