/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "lwip/err.h"
#include "lwip/udp.h"
#if defined (__arm__) || defined (__aarch64__)
#include "xil_printf.h"
#endif


int transfer_data() {
	return 0;
}

void print_app_header()
{
	xil_printf("\n\r\n\r-----lwIP UDP streaming server ------\n\r");
}

#if 0
void recv_callback(void *arg, struct udp_pcb *pcb,
                               struct pbuf *p, struct ip_addr *addr, u16_t port)
{
	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		return;
	}
	xil_printf("Sending data");

}
#endif


int start_application()
{
	struct udp_pcb *pcb;
	err_t err;
	unsigned port = 35912;

	/* create new TCP PCB structure */
	pcb = udp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */

	ip_addr_t dest;
	IP4_ADDR(&dest, 192, 168, 1, 75);
	err = udp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	xil_printf("Sending packets...\n");
	while(1) {
		int i = 5;
		struct pbuf *data = pbuf_alloc(PBUF_TRANSPORT, sizeof(int), PBUF_RAM);
		if(data == NULL) {
			xil_printf("Failed to allocate");
			continue;
		}
		if(pbuf_take(data, &i, sizeof(int)) != ERR_OK) {
			xil_printf("Error in pbuf_take\n");
			break;
		}

		udp_sendto(pcb, data, &dest, port);
		pbuf_free(data);
		usleep(100000);
	}

	xil_printf("UDP streaming server started @ port %d\n\r", port);

	return 0;
}
