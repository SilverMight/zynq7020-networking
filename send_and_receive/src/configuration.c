#include "conversion.h"
#include "configuration.h"
#include <stdint.h>
#include "xil_printf.h"
#include "wanda_errorcodes.h"

int wandaNumActiveSensors = 0;
Sensor wandaSensors[WANDA_NUM_SENSORS];


int process_config_command(uint32_t command) {
	// too many sensors!
	if(wandaNumActiveSensors == WANDA_NUM_SENSORS) {
		return 1;
	}
	Sensor sensor;

	// Channel number is Bits [0:5]
	int channelNumber = (command & (0xFFFFFFFF >> 26));

	// Sensor type is [6:8]
	sensor.sensorType = ((command >> 6) & (0x7));

	// Serial number [9:15]
	sensor.serialNumber = ((command >> 9) & (0x7F));

	// LOGIC TO CHECK IF CORRECT
	if(sensor.sensorType >= max_num_sensors) {
		xil_printf("Invalid sensor type\n");
		return 1;
	}


	wandaSensors[channelNumber] = sensor;

	return 0;
}

void print_all_sensors() {
	for(int i = 0; i < WANDA_NUM_SENSORS; i++) {
		Sensor sensor = wandaSensors[i];
		if(sensor.serialNumber != WANDA_UNINITIALIZED_VALUE && sensor.sensorType != WANDA_UNINITIALIZED_VALUE) {
			xil_printf("Sensor %u: sensor type %u, serial no %u\n", i, sensor.sensorType, sensor.serialNumber);
		}
	}
}

void initialize_sensor_config() {
	for(int i = 0; i < WANDA_NUM_SENSORS; i++) {
		wandaSensors[i].sensorType = WANDA_UNINITIALIZED_VALUE;
		wandaSensors[i].serialNumber = WANDA_UNINITIALIZED_VALUE;
	}
}
