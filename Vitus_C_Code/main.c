#include <stdio.h>
#include "platform.h"

#include <stdlib.h>
#include "xparameters.h"
#include "xgpio.h"
#include "xil_io.h"

// Globals
XGpio gpio0, gpio2, gpio3;

void initialize()
{
    // Inputs
    XGpio_Initialize(&gpio0, XPAR_AXI_GPIO_0_BASEADDR);
    XGpio_SetDataDirection(&gpio0, 1, 0x00); // A (To Hardware)
    XGpio_SetDataDirection(&gpio0, 2, 0x00); // B

    // Result/Buttons
    XGpio_Initialize(&gpio2, XPAR_AXI_GPIO_2_BASEADDR);
    XGpio_SetDataDirection(&gpio2, 1, 0xFF); // Result (From Hardware)
    XGpio_SetDataDirection(&gpio2, 2, 0xFF); // Buttons

    // Buttons/Switches
    XGpio_Initialize(&gpio3, XPAR_AXI_GPIO_3_BASEADDR);
    XGpio_SetDataDirection(&gpio3, 1, 0xFF); // SWS
    XGpio_SetDataDirection(&gpio3, 2, 0x00); // LEDS
}

// Hardware Accellerator "Driver"
u32 unsigned_adder(u32 a, u32 b)
{
    // Write A/B
    XGpio_DiscreteWrite(&gpio0, 1, a);
    XGpio_DiscreteWrite(&gpio0, 2, b);
    
    // Read Result (Assumes data is ready by function call)
    return XGpio_DiscreteRead(&gpio2, 1) & 0xF; // Lower 4 bits is result;
}


int main() {
    initialize();
    while (1) {
        // Read Switches
        u32 switches = XGpio_DiscreteRead(&gpio3, 1);
        u32 a = switches & 0x0F; // Lower 4
        u32 b = (switches & 0xF0) >> 4; // Upper 4

        // Use Adder
        u32 result = unsigned_adder(a, b);

        // Write LEDs
        XGpio_DiscreteWrite(&gpio3, 2, result);
    }

    return 0;
}
