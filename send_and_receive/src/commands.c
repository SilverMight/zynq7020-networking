#include "commands.h"
#include "configuration.h"

#include <stdio.h>
#include "xil_printf.h"

#define FILL_BIT 1

int processCommand(int command) {
	switch(command >> 24) {
		case 0xCF:
			return process_config_command(command);
			break;
	}

}
