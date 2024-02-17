#include "conversion.h"
#include "configuration.h"
#include <stdint.h>



const static conversionFunction conversionFunctionsArray[] = {
    convertPressure,
};

const static int wandaVoltageCoefficients[2][WANDA_NUM_CHANNELS] = {
0
};

const static int pressureCoefficients[2][WANDA_NUM_SENSORS_PER_TYPE] = {
0
};

double convertPressure(double voltage, uint8_t serialNumber) {
	// TODO: implement serial number coefficient
    return voltage * 0.5 + 50;
}


double convertToVoltage(int32_t dout, uint8_t channelNumber) {
	// TODO: implement voltage coefficients
	return (double) ((int) (dout << 8) >> 8);
}

double applyConversion(uint32_t dout, Sensor sensor, uint8_t channelNumber) {
	conversionFunction function = conversionFunctionsArray[sensor.sensorType];
	return function(convertToVoltage(dout, channelNumber), sensor.serialNumber);
}
