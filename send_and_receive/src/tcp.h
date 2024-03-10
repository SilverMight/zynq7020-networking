/*
 * tcp.h
 *
 *  Created on: Jan 24, 2024
 *      Author: silvermight
 */

#ifndef SRC_TCP_H_
#define SRC_TCP_H_

err_t recv_callback(void *arg, struct tcp_pcb *tpcb,
                               struct pbuf *p, err_t err);
err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err);
int start_application(struct tcp_pcb* pcb);

int new_tcp_pcb(struct tcp_pcb** pcb);



#endif /* SRC_TCP_H_ */
