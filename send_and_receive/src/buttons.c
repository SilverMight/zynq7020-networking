#include "buttons.h"

uint32_t buttonState = 0;

WandaError process_buttons(uint32_t command) {
	// We only care about [0:15]
	int newState = EXTRACT_BUTTON_STATE(command);

	int updatedButtons = buttonState ^ newState;

	for(int button = 0; button < WANDA_NUM_BUTTONS; button++) {
		if(updatedButtons & (1 << button)) {

		}
	}

}


