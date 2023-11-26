

int processCommand(int command) {

	switch(command) {
	case 1:
	case 2:
		return 1;
	case 3:
		return 0xdeadbeef;
	}
}
