/*
 * commands.h
 *
 *  Created on: Jan 24, 2024
 *      Author: silvermight
 */

#ifndef SRC_COMMANDS_H_
#define SRC_COMMANDS_H_
#include <stdint.h>
#include "wanda_errorcodes.h"

WandaError processCommand(uint32_t command);

#endif /* SRC_COMMANDS_H_ */
