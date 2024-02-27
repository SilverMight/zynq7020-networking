#include "commands.h"
#include "configuration.h"
#include "buttons.h"

#include <stdio.h>
#include "xil_printf.h"
#include "wanda_errorcodes.h"

WandaError processCommand(uint32_t command) {
	xil_printf("Command %x\n", command);
	switch(command >> 24) {
	// Config
	case 0xCF:
		xil_printf("Process config command\n", command);
		return process_config_command(command);
		break;
	// Print sensors
	case 0x55:
		xil_printf("Print all sensors\n", command);
		print_all_sensors();
		return WANDA_ERR_OK;
		break;
	// Button command
	case 0xBC:
		xil_printf("Print buttons");
		return process_buttons(command);
	// INVALID
	default:
		return WANDA_ERR_INVALID_COMMAND;
	}


}
