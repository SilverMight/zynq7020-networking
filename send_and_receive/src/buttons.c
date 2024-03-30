#include "buttons.h"
#include "xil_printf.h"
#include "gpio.h"

uint32_t buttonState = 0;

void process_buttons(uint32_t command) {
	// We only care about [0:15]
	/*
	int newState = EXTRACT_BUTTON_STATE(command);

	int updatedButtons = buttonState ^ newState;
	*/

	// Send 8 bits to GPIO
	GpioSet(0x000000FF & command);

	// TODO: logic to make sure button state is OK
	//buttonState = updatedButtons;

}


