#ifndef WANDA_CAN_H
#define WANDA_CAN_H

#include "xil_types.h"
#define XCANPS_MAX_FRAME_SIZE_IN_WORDS 16
extern u32 RxFrame[XCANPS_MAX_FRAME_SIZE_IN_WORDS];

int CanPsConfig();
int Can_SendFrame(uint32_t data);
int Can_SendFrame64(uint64_t data);
int Can_RecvFrame();

#endif


