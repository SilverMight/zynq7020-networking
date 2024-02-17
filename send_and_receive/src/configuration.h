#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <stdint.h>

#define WANDA_NUM_SENSORS 32


typedef struct {
	int sensorType : 3;
	int serialNumber : 7;
} Sensor;

// Index by channel number
extern Sensor wandaSensors[WANDA_NUM_SENSORS];
extern int wandaNumActiveSensors;



// [8:4] is reserved for sensor number, [3:0] for function type
int process_config_command(int32_t command);


#endif
