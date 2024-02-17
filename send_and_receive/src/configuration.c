#include "conversion.h"
#include "configuration.h"
#include <stdint.h>


int process_config_command(int32_t command) {
	Sensor sensor;

	// Channel number is Bits [0:5]
	int channelNumber = (command & (0xFFFFFFFF >> 26));

	// Sensor type is [6:8]
	sensor.sensorType = ((command >> 6) & (0x7));

	// Serial number [9:15]
	sensor.serialNumber = ((command >> 9) & (0x7F));

	// LOGIC TO CHECK IF CORRECT


	wandaSensors[channelNumber] = sensor;
	wandaNumActiveSensors++;

	return 0;
}
