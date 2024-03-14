#ifndef KXR_MCM_H
#define KXR_MCM_H

// Global Constants
#define SERVO_COUNT 8
#define SOLENOID_COUNT 8
#define RELAY_COUNT 8

// Servo States
#define SERVO_MAX 180
#define SERVO_MIN 0

// Solenoid States
#define OPEN 1
#define CLOSE 0

// Relay States
#define ON 1
#define OFF 0

// Fill Shorthands
#define FUEL_FILL &(solenoids[0])
#define OXIDIZER_FILL &(solenoids[1])
#define COMPRESSOR_FILL &(solenoids[2])

// Vent Shorthands
#define FUEL_VENT &(solenoids[3])
#define OXIDIZER_VENT &(solenoids[4])
#define COMPRESSOR_VENT &(solenoids[5])

// Servo Shorthands
#define FUEL_DC &(servos[0])
#define OXI_DC &(servos[1])
#define PSI_DC &(servos[2])

// Relay Shorthands
#define ARM &(relays[6])
#define IGNITION &(relays[7])

// Switch Shorthands
#define MCM_POWER_SWITCH_BIT (1 << 0)
#define MCM_FUEL_FILL_SWITCH_BIT (1 << 1)
#define MCM_FUEL_VENT_SWITCH_BIT (1 << 2)
#define MCM_OXI_FILL_SWITCH_BIT (1 << 3)
#define MCM_OXI_VENT_SWITCH_BIT (1 << 4)
#define MCM_PSI_FILL_SWITCH_BIT (1 << 5)
#define MCM_PSI_VENT_SWITCH_BIT (1 << 6)
#define MCM_QUICK_DC_SWITCH_BIT (1 << 7)
#define MCM_ARM_SWITCH_BIT (1 << 12)
#define MCM_IGNITION_SWITCH_BIT (1 << 13)
#define MCM_ABORT_SWITCH_BIT (1 << 14)

// DATA TYPES AND STRUCTURES


typedef struct servo {
    unsigned int *address;
    unsigned int position;
    bool feedback;
} Servo;

typedef struct solenoid {
    unsigned int *address;
    bool state;
    bool feedback;
} Solenoid;

typedef struct relay {
    unsigned int *address;
    bool active;
    bool feedback;
} Relay;

// GLOBAL VARIABLES

extern Command current;
extern Servo servos[SERVO_COUNT];
extern Solenoid solenoids[SOLENOID_COUNT];
extern Relay relays[RELAY_COUNT];

// CONFIGURATION FUNCTIONS

// CONVERSION FUNCTIONS

// Set Servo's Angle
bool setServo(Servo *servo, unsigned int to);

// Set Solenoid's State
bool setSolenoid(Solenoid *solenoid, unsigned int to);

// Set Relay's State
bool setRelay(Relay *relay, unsigned int to);

// CONTROL MACROS

// Open Line
bool openLine(Solenoid *line);

// Close Line
bool closeLine(Solenoid *line);

// Fill All
bool fillAll();

bool fillNone();

// Vent
bool ventAll();

bool ventNone();

bool quickDisconnectAll();

bool abortMacro();

bool arm();

bool ignition();

bool allServosMin();

bool allSolenoidsOff();

bool allRelaysOff();

bool allOff();

// Decode Current Command
bool run();

#endif //KXR_MCM_H
