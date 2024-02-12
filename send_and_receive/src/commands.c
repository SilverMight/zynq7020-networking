#include "commands.h"

#include <stdio.h>
#include "xil_printf.h"

#define FILL_BIT 1

int processCommand(int command) {

	switch(command) {
	case 1:
		xil_printf("Received 1, returning 0\n");
		return 0;
	case 1 << FILL_BIT:
		xil_printf("fill command");
	default:
		xil_printf("Unknown command, returning 2\n");
		return 2;
	}
}
