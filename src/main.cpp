#include "system.h"
#include "program.h"

int main(void) {
    HAL_Init();

    Program p;

    // Any required Startup
    p.Startup();

    // Main Loop
    p.MainLoop();
}

void SysTick_Handler(void) {
    HAL_IncTick();
}