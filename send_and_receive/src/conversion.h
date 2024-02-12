#ifndef CONVERSION_H
#define CONVERSION_H
#include <stdint.h>

typedef double(*conversionFunction) (double data);

double convertToDouble(uint32_t data);
double convertPressure(double data);
double convertVoltage(double data);

conversionFunction conversionFunctionsArray[] = {
    &convertVoltage,
    &convertPressure
};

enum conversionState {
    voltage,
    pressure,
};


#endif
