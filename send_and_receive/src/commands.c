#include "commands.h"

#include <stdio.h>
#include "xil_printf.h"

int processCommand(int command) {

	switch(command) {
	case 1:
		xil_printf("Received 1, returning 0\n");
		return 0;
	case 2:
		xil_printf("Received 2, returning 1\n");
		return 1;
	default:
		xil_printf("Unknown command, returning 2\n");
		return 2;
	}
}
