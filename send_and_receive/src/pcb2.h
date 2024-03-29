#ifndef WANDA_PCB2_H
#define WANDA_PCB2_H
#include <stdint.h>
#include "wanda_errorcodes.h"

WandaError pcb_request_can_data(uint32_t command);
WandaError pcb_stream_can_data();

#endif
