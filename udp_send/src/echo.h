#ifndef ECHO_H
#define ECHO_H

void print_app_header();
int start_application();
int static_send(struct udp_pcb * pcb, ip_addr_t * dest_ip, unsigned port);
int transfer_data();
int udp_send_init(struct udp_pcb* pcb_out);

#endif // !ECHO_H

