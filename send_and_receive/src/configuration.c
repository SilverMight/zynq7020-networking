#include "conversion.h"
#include "configuration.h"
#include <stdint.h>
#include "xil_printf.h"
#include "wanda_errorcodes.h"

Sensor wandaSensors[WANDA_NUM_SENSORS];


int process_config_command(uint32_t command) {
	Sensor sensor;

	// Channel number is Bits [0:5]
	int channelNumber = GET_CHANNEL_NUMBER(command);

	// Sensor type is [6:8]
	sensor.sensorType = (SensorTypes) GET_SENSOR_TYPE(command);


	// Serial number [9:15]
	sensor.serialNumber = GET_SERIAL_NUMBER(command);

	// check if valid sensor
	if(sensor.sensorType < 0 || sensor.sensorType >= max_sensor_types) {
		xil_printf("Invalid sensor type %d\n", sensor.sensorType);
		return WANDA_ERR_SENSOR_INVALID_TYPE;
	}


	wandaSensors[channelNumber] = sensor;

	return WANDA_ERR_OK;
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
