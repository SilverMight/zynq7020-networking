/*
 * buttons.h
 *
 *  Created on: Feb 23, 2024
 *      Author: silvermight
 */

#ifndef SRC_BUTTONS_H_
#define SRC_BUTTONS_H_
#include "wanda_errorcodes.h"
#include <stdint.h>

#define WANDA_NUM_BUTTONS 15
#define EXTRACT_BUTTON_STATE(command) (command & (0x7FFF))

void process_buttons(uint32_t command);

extern uint32_t buttonState;

#endif /* SRC_BUTTONS_H_ */
