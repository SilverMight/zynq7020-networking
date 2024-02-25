#include "commands.h"
#include "configuration.h"

#include <stdio.h>
#include "xil_printf.h"
#include "wanda_errorcodes.h"

WandaError processCommand(uint32_t command) {
	xil_printf("Command %x\n", command);
	switch(command >> 24) {
		case 0xCF:
			xil_printf("Process config command\n", command);
			return process_config_command(command);
			break;
		case 0x55:
			xil_printf("Print all sensors\n", command);
			print_all_sensors();
			return WANDA_ERR_OK;
			break;

		// INVALID
		default:
			return 1;
	}


}
