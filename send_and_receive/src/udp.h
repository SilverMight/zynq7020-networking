#ifndef ECHO_H
#define ECHO_H
#include "lwip/udp.h"

#define WANDA_UDP_PORT 8888
extern ip_addr_t dest_ip;
extern struct udp_pcb *upcb;


int send_data(void * data, int data_size);
int udp_send_init(struct udp_pcb** pcb_out);

#endif // !ECHO_H

