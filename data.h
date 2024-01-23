#include <stdint.h>


#define SENSOR_CHANNELS 8

#define EXTRACT_24_BITS (value) ((value) & 0x00FFFFFF)

typedef struct {
    int32_t dim0[SENSOR_CHANNELS]; // 
    int32_t maxChannel; // periodic data, probably have some function to pull it
} DIMData;

/*
 * Have a function for this that takes whatever data we received over the network
 * (likely ASCII), and run through a switch statement to return proper command
 * Alternatively if we use an integral type we can just cast it to this enum.
*/
typedef enum {
    VENT_OPEN,
    VENT_CLOSE,
    FILL_START,
    FILL_STOP,
    LIGHT_E_MATCH,
} Command;
