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

#include "udp.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "data.h"

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

void udp_echo_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct
					ip_addr *addr, u16_t port)
{
    if (p != NULL) {
        /* send received packet back to sender */
        udp_sendto(pcb, p, addr, port);
        /* free the pbuf */
        pbuf_free(p);
    }
}

int udp_send_init(struct udp_pcb** pcb_out) {
    *pcb_out = udp_new();
	if (!*pcb_out) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}
    return 0;
}

int static_send(struct udp_pcb * pcb, ip_addr_t * dest_ip, unsigned port) {
	int numDataPoints = 5;

	err_t err;
	struct pbuf *data; // packet we send over the network
	char buf[1 + (numDataPoints * sizeof(int))]; // an array of bytes


    // Should extrapolate this into a data to string function
    // (which we could call with data we fetched)
	int * fakedata = get_n_random_numbers(numDataPoints, 10);

	/*
	snprintf(buf, 100, "%d,%d,%d,%d,%d\n", fakedata[0], fakedata[1], fakedata[2], fakedata[3], fakedata[4]); // who needs a CSV library anyway
	int buflen = strlen(buf);
	*/

	buf[0] = 0xAA; // sync word for telemetry viewer
	size_t offset = 1;
	for(int i = 0; i < numDataPoints; i++) {
		memcpy(buf + offset, &fakedata[i], sizeof(int));
		offset += sizeof(int);
	}

	//xil_printf("%d,%d,%d,%d,%d\n", fakedata[0], fakedata[1], fakedata[2], fakedata[3], fakedata[4]); // who needs a CSV library anyway
	//xil_printf("%c, %d,%d,%d,%d,%d\n", *(buf), *(buf + 1), *(buf + 5), *(buf + 9), *(buf + 13), *(buf + 17) );

	int buflen = sizeof(buf);

	data = pbuf_alloc(PBUF_TRANSPORT, buflen, PBUF_RAM);

	if(data == NULL) {
		xil_printf("Failed to allocate, OOM");
		return -1;
	}

	if(pbuf_take(data, buf, buflen) != ERR_OK) {
		xil_printf("Error in pbuf_take\n");
		return -1;
	}

	err = udp_sendto(pcb, data, dest_ip, port);
	if (err != ERR_OK) {
		xil_printf("Failed to send!\n");
        return -1;
	}

	free(fakedata);
	pbuf_free(data);
	return 0;
}

// Currently useless - will replace with TCP
int start_application()
{
	struct udp_pcb *pcb;
	err_t err;
	unsigned port = 39000;

	/* create new TCP PCB structure */
	pcb = udp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = udp_bind(pcb, IP_ADDR_ANY, port);
	if (err != 0) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}


	/* Receive data */
	//udp_recv(pcb, udp_echo_recv, NULL);

	xil_printf("UDP streaming server started @ port %d\n\r", port);

	return 0;
}
