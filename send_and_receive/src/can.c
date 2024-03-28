#include "xcanps.h"
#include "xparameters.h"
#include "xil_printf.h"

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define CAN_DEVICE_ID	0x1DA

/*
 * Maximum CAN frame length in words.
 */
#define XCANPS_MAX_FRAME_SIZE_IN_WORDS (sizeof(u32)*4 / sizeof(u32))

#define FRAME_DATA_LENGTH 		4  /* Frame Data field length */

/*
 * Message Id Constant.
 */
#define TEST_MESSAGE_ID 0x1DA

/*
 * The Baud Rate Prescaler Register (BRPR) and Bit Timing Register (BTR)
 * are setup such that CAN baud rate equals 40Kbps, assuming that the
 * the CAN clock is 24MHz. The user needs to modify these values based on
 * the desired baud rate and the CAN clock frequency. For more information
 * see the CAN 2.0A, CAN 2.0B, ISO 11898-1 specifications.
 */

/*
 * Timing parameters to be set in the Bit Timing Register (BTR).
 * These values are for a 40 Kbps baudrate assuming the CAN input clock
 frequency
 * is 24 MHz.
 */
#define TEST_BTR_SYNCJUMPWIDTH		3
#define TEST_BTR_SECOND_TIMESEGMENT	1
#define TEST_BTR_FIRST_TIMESEGMENT	2

/*
 * The Baud rate Prescalar value in the Baud Rate Prescaler Register (BRPR)
 * needs to be set based on the input clock  frequency to the CAN core and
 * the desired CAN baud rate.
 * This value is for a 40 Kbps baudrate assuming the CAN input clock frequency
 * is 24 MHz.
 */
#define TEST_BRPR_BAUD_PRESCALAR	31

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

int CanPsConfig();
int SendFrame();
int RecvFrame();

/************************** Variable Definitions *****************************/

/*
 * Buffers to hold frames to send and receive. These are declared as global so
 * that they are not on the stack.
 * These buffers need to be 32-bit aligned
 */
static u32 TxFrame[XCANPS_MAX_FRAME_SIZE_IN_WORDS];
static u32 RxFrame[XCANPS_MAX_FRAME_SIZE_IN_WORDS];

/* Driver instance */
static XCanPs Can;
static XCanPs* InstancePtr = &Can;


int CanPsConfig()
{
	int Status;
	XCanPs *CanInstPtr = &Can;
	XCanPs_Config *ConfigPtr;

	/*
	 * Initialize the Can device.
	 */
	ConfigPtr = XCanPs_LookupConfig(CAN_DEVICE_ID);
	if (CanInstPtr == NULL) {
		return XST_FAILURE;
	}
	Status = XCanPs_CfgInitialize(CanInstPtr,
					ConfigPtr,
					ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enter Configuration Mode so we can setup Baud Rate Prescaler
	 * Register (BRPR) and Bit Timing Register (BTR).
	 */
	XCanPs_EnterMode(CanInstPtr, XCANPS_MODE_CONFIG);
	while(XCanPs_GetMode(CanInstPtr) != XCANPS_MODE_CONFIG);

	/*
	 * Setup Baud Rate Prescaler Register (BRPR) and
	 * Bit Timing Register (BTR).
	 */
	XCanPs_SetBaudRatePrescaler(CanInstPtr, TEST_BRPR_BAUD_PRESCALAR);
	XCanPs_SetBitTiming(CanInstPtr, TEST_BTR_SYNCJUMPWIDTH,
				TEST_BTR_SECOND_TIMESEGMENT,
				TEST_BTR_FIRST_TIMESEGMENT);

	/*
	 * Enter Loop Back Mode.
	 */
	XCanPs_EnterMode(CanInstPtr, XCANPS_MODE_NORMAL);

	while(XCanPs_GetMode(CanInstPtr) != XCANPS_MODE_NORMAL);
	/*
	 * Send a frame, receive the frame via the loop back and verify its
	 * contents.
	 */
}


/*****************************************************************************/
/**
*
* Send a CAN frame.
*
* @param	InstancePtr is a pointer to the driver instance
*
* @return	XST_SUCCESS if successful, a driver-specific return code if not.
*
* @note
*
* This function waits until TX FIFO has room for at least one frame before
* sending a frame. So this function may block if the hardware is not built
* correctly.
*
******************************************************************************/
int SendFrame(uint32_t data)
{
	u8 *FramePtr;
	int Index;
	int Status;

	//int erm_pl = 0xBEEF;


	/*
	 * Create correct values for Identifier and Data Length Code Register.
	 */
	TxFrame[0] = (u32)XCanPs_CreateIdValue((u32)TEST_MESSAGE_ID, 0, 0, 0, 0);
	TxFrame[1] = (u32)XCanPs_CreateDlcValue((u32)FRAME_DATA_LENGTH);
	TxFrame[2] = (u32)data;
	//TxFrame[3] = (u16)erm_pl;

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */
	//FramePtr = (u8 *)(&TxFrame[2]);
	for (Index = 0; Index < 4; Index++) {
		xil_printf("%X\r\n", TxFrame[Index]);
		//*FramePtr++ = (u8)Index;
	}

	/*
	 * Wait until TX FIFO has room.
	 */
	while (XCanPs_IsTxFifoFull(InstancePtr) == TRUE);

	/*
	 * Now send the frame.
	 *
	 * Another way to send a frame is keep calling XCanPs_Send() until it
	 * returns XST_SUCCESS. No check on if TX FIFO is full is needed anymore
	 * in that case.
	 */
	Status = XCanPs_Send(InstancePtr, TxFrame);

	return Status;
}


/*****************************************************************************/
/**
*
* This function receives a frame and verifies its contents.
*
* @param	InstancePtr is a pointer to the driver instance.
*
* @return	XST_SUCCESS if successful, a driver-specific return code if not.
*
* @note
*
* This function waits until RX FIFO becomes not empty before reading a frame
* from it. So this function may block if the hardware is not built
* correctly.
*
******************************************************************************/
int RecvFrame()
{
	u8 *FramePtr;
	int Status;
	int Index;

	/*
	 * Wait until a frame is received.
	 */
	while (XCanPs_IsRxEmpty(InstancePtr) == TRUE);

	/*
	 * Receive a frame and verify its contents.
	 */
	Status = XCanPs_Recv(InstancePtr, RxFrame);
	if (Status == XST_SUCCESS) {
		/*
		 * Verify Identifier and Data Length Code.
		 */

		/*
		if (RxFrame[0] != (u32)ermy)
			return XST_LOOPBACK_ERROR;
		*/

		/*

		if ((RxFrame[1] & ~XCANPS_DLCR_TIMESTAMP_MASK) != TxFrame[1])
			return XST_LOOPBACK_ERROR;
		*/

		/*
		 * Verify Data field contents.
		 */

		//FramePtr = (u8 *)(&RxFrame[2]);



		for (Index = 0; Index < 4; Index++) {

			xil_printf("%X\r\n", RxFrame[Index]);

			/*
			if (*FramePtr++ != (u8)Index) {
				return XST_LOOPBACK_ERROR;
			}
			*/
		}

	}

	return Status;
}
