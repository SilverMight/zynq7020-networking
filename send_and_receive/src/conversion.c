#include "conversion.h"
#include <stdint.h>

#define NORMALIZATION_FACTOR 0x80000

double convertVoltage(double data) {
    return data * 0.5;
}

double convertPressure(double data) {
    return data * 0.5 + 50;
}


double convertToDouble(uint32_t data) {
    int normalizedSignedInt = (int) (data) - NORMALIZATION_FACTOR;

    return (double) (normalizedSignedInt);
}

extern inline double applyConversion(uint32_t data, conversionFunction func) {
    return func(convertToDouble(data));
}
