#ifndef ECHO_H
#define ECHO_H
#include "lwip/udp.h"

void print_app_header();
int start_application();
int transfer_data();
int static_send(struct udp_pcb * pcb, ip_addr_t * dest_ip, unsigned port);
int udp_send_init(struct udp_pcb** pcb_out);

#endif // !ECHO_H

