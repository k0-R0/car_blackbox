/* 
 * File:   uart.h
 * Author: bmeno
 *
 * Created on June 30, 2026, 4:02 PM
 */

#ifndef UART_H
#define	UART_H

void init_uart(void);
void uart_transmit_char(unsigned char);
void uart_transmit_str(unsigned char *);
unsigned char uart_receive(void);
#endif	/* UART_H */

