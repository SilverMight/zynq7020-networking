#ifndef CONVERSION_H
#define CONVERSION_H
#include <stdint.h>

#define WANDA_NUM_SENSOR_TYPES 8
#define WANDA_NUM_CHANNELS 2
#define WANDA_NUM_SENSORS_PER_TYPE 8


typedef double(*conversionFunction) (double voltage, uint8_t channelType);

double convertToVoltage(int32_t dout, uint8_t channelNumber);

double convertPressure(double data, uint8_t serialNumber);


enum conversionState {
    pressure, // 0
	loadcell, // 1

	max_num_sensors
};


#endif
