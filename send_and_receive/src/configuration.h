#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <stdint.h>
#include "conversion.h"

#define WANDA_NUM_SENSORS 32
#define WANDA_UNINITIALIZED_VALUE 0

#define GET_CHANNEL_NUMBER(command) ((command) & 0x3F)
#define GET_SENSOR_TYPE(command) (((command) >> 6) & 0x7)
#define GET_SERIAL_NUMBER(command) (((command) >> 9) & 0x7F)

typedef struct {
	SensorTypes sensorType : 3;
	unsigned int serialNumber : 7;
} Sensor;

// Index by channel number
extern Sensor wandaSensors[WANDA_NUM_SENSORS];


// [8:4] is reserved for sensor number, [3:0] for function type
int process_config_command(uint32_t command);

void print_all_sensors();

void initialize_sensor_config();


#endif
