#pragma once

#include "system.h"
#include "Drivers/Device.h"

class DigitalPin : public Device {
    protected:
        GPIO_TypeDef *gpiox;
        uint8_t pin_number;
    public:
        DigitalPin(GPIO_TypeDef *gpioPort, uint8_t pin);
        virtual void InitDevice()=0;
        //void ConfigureOutput();
        ~DigitalPin();
};

class OutputPin : public DigitalPin {
    public:
        OutputPin(GPIO_TypeDef *gpioPort, uint8_t pin);
        virtual void InitDevice();
        void Toggle();
        OutputPin& operator =(GPIO_PinState pinState);
};