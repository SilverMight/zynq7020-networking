#include "xil_printf.h"
#include "xstatus.h"

#include "pcb2.h"
#include "can.h"
#include "wanda_errorcodes.h"
#include "udp.h"

#define WANDA_NUM_CAN_DATA_POINTS 22

WandaError pcb_request_can_data(uint32_t command) {
	Can_SendFrame(command);

	// Read data
	xil_printf("READING\n");
	for(int i = 0; i < WANDA_NUM_CAN_DATA_POINTS; i++) {
		xil_printf("Reading data point %d\n", i);
		Can_RecvFrame();
	}


}

//static int hit[22];

WandaError pcb_stream_can_data() {

	int status = Can_RecvFrame();

	if(status == XST_NO_DATA) {
		xil_printf("CAN DATA Stream: No data ready\n");
		return WANDA_ERR_OK;
	}

	if(status != XST_SUCCESS) {
		xil_printf("CAN DATA Stream: Unknown failure!\n");
		return WANDA_ERR_CAN_STREAM_FAILURE;
	}


	u8 * FramePointer = (u8 *) (&RxFrame[2]);

	// Merge into an actual 64-bit integer to send
	uint64_t data;
	for(int i = 0; i < 5; i++) {
		data |= ((uint64_t) FramePointer[i]) << (i * 8);
	}

	send_data(&data, sizeof(data));
	return WANDA_ERR_OK;
}
