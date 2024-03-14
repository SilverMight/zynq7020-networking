#include <stdio.h>
#include "mcm.h"
#include "error.h"

Command current;

Solenoid solenoids[SOLENOID_COUNT] = {{NULL, OFF, ON},
                                      {NULL, OFF, ON},
                                      {NULL, OFF, ON},
                                      {NULL, OFF, ON},
                                      {NULL, OFF, ON},
                                      {NULL, OFF, ON},
                                      {NULL, OFF, ON},
                                      {NULL, OFF, ON}};

Relay relays[RELAY_COUNT] = {{NULL, OFF, ON},
                             {NULL, OFF, ON},
                             {NULL, OFF, ON},
                             {NULL, OFF, ON},
                             {NULL, OFF, ON},
                             {NULL, OFF, ON},
                             {NULL, OFF, ON},
                             {NULL, OFF, ON}};


typedef unsigned char bool;


bool setServo(Servo *servo, unsigned int to) {
    if ((to > SERVO_MAX) or (servo->position > SERVO_MAX)) {
        return false;
    } else {
        servo->position = to;
        return servo->feedback;
    }
}

bool setSolenoid(Solenoid *solenoid, unsigned int to) {
    if (not solenoid->feedback) {
        return OFF;
    } else {
        solenoid->state = to;
        return solenoid->feedback;
    }
}

bool setRelay(Relay *relay, unsigned int to) {
    if (not relay->feedback) {
        return OFF;
    } else {
        relay->active = to;
        return relay->feedback;
    }
}

bool openLine(Solenoid *line) {
    return setSolenoid(line, OPEN);
}

bool closeLine(Solenoid *line) {
    return setSolenoid(line, CLOSE);
}

bool fillAll() {
    if (not ABORT_SWITCH) {
        return openLine(FUEL_FILL) and openLine(OXIDIZER_FILL) and openLine(COMPRESSOR_FILL);
    } else return false;
}

bool fillNone() {
    return closeLine(FUEL_FILL) and closeLine(OXIDIZER_FILL) and closeLine(COMPRESSOR_FILL);
}

bool ventAll() {
    return openLine(FUEL_VENT)
           and openLine(OXIDIZER_VENT)
           and openLine(COMPRESSOR_VENT);
}

bool ventNone() {
    return closeLine(FUEL_VENT)
           and closeLine(OXIDIZER_VENT)
           and closeLine(COMPRESSOR_VENT);
}

bool quickDisconnectAll() {
    return setServo(FUEL_DC, 180)
           and setServo(OXI_DC, 180)
           and setServo(PSI_DC, 180);
}

bool abortMacro() {
    return fillNone()
           and ventAll();
}

bool arm() {
    return setRelay(ARM, true);
}

bool ignition() {
    return setRelay(IGNITION, true);
}

bool allServosMin() {
    bool out = true;
    for (int s = 0; s < SERVO_COUNT; ++s) {
        out = out and setServo(&servos[s], SERVO_MIN);
    }
    return out;
}

bool allSolenoidsOff() {
    bool out = true;
    for (int s = 0; s < SOLENOID_COUNT; ++s) {
        out = out and setSolenoid(&solenoids[s], OFF);
    }
    return out;
}

bool allRelaysOff() {
    bool out = true;
    for (int r = 0; r < RELAY_COUNT; ++r) {
        out = out and setRelay(&relays[r], OFF);
    }
    return out;
}

bool allOff() {
    return allServosMin() and allSolenoidsOff() and allRelaysOff();
}

MCMStatus run(uint32_t command) {
	if(!(command & MCM_POWER_SWITCH_BIT)) return MCM_ERR_OFF;
	if (ABORT_SWITCH) {
		return abortMacro();
	} else {
		if (QUICK_DC_SWITCH) {
			quickDisconnectAll();
		} else {
			allServosMin();
		}
		if (FUEL_FILL_SWITCH or FUEL_VENT_SWITCH) {
			if (FUEL_VENT_SWITCH) {
				closeLine(FUEL_FILL);
				openLine(FUEL_VENT);
			} else {
				closeLine(FUEL_VENT);
				openLine(FUEL_FILL);
			}
		} else {
			closeLine(FUEL_VENT);
			closeLine(FUEL_FILL);
		}
		if (OXI_FILL_SWITCH or OXI_VENT_SWITCH) {
			if (OXI_VENT_SWITCH) {
				closeLine(OXIDIZER_FILL);
				openLine(OXIDIZER_VENT);
			} else {
				closeLine(OXIDIZER_VENT);
				openLine(OXIDIZER_FILL);
			}
		} else {
			closeLine(OXIDIZER_VENT);
			closeLine(OXIDIZER_FILL);
		}
		if (PSI_FILL_SWITCH or PSI_VENT_SWITCH) {
			if (PSI_VENT_SWITCH) {
				closeLine(COMPRESSOR_FILL);
				openLine(COMPRESSOR_VENT);
			} else {
				closeLine(COMPRESSOR_VENT);
				openLine(COMPRESSOR_FILL);
			}
		} else {
			closeLine(COMPRESSOR_VENT);
			closeLine(COMPRESSOR_FILL);
		}
		if (ARM_SWITCH and not
				(FUEL_FILL_SWITCH
						or OXI_FILL_SWITCH
						or PSI_FILL_SWITCH)) {
			arm();
			if (IGNITION_SWITCH and QUICK_DC_SWITCH) {
				return ignition();
			}
		}
	}
}
return false;
}
