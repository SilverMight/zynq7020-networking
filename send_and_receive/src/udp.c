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

ip_addr_t dest_ip;
struct udp_pcb *upcb;

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

int send_data(void * data, int data_size) {
	err_t err;
	struct pbuf *data_packet; // packet we send over the network

	data_packet = pbuf_alloc(PBUF_TRANSPORT, data_size, PBUF_RAM);

	if(data_packet == NULL) {
		xil_printf("Failed to allocate, OOM\n");
		return -1;
	}

	if(pbuf_take(data_packet, data, data_size) != ERR_OK) {
		xil_printf("Error in pbuf_take\n");
		return -1;
	}

	err = udp_sendto(upcb, data_packet, &dest_ip, WANDA_UDP_PORT);
	if (err != ERR_OK) {
		xil_printf("Failed to send!\n");
        return -1;
	}

	pbuf_free(data_packet);
	return 0;
}
