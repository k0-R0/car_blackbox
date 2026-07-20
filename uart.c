#include "blackbox.h"

void init_uart(void) {
    //set transmitter and receiver pins for o/p and i/p
    TRISC6 = 0;
    TRISC7 = 1;
    //TXSTA configuration
    //8 bit transmission
    TX9 = 0;
    //Async mode
    SYNC = 0;
    //send break character bit
    SENDB = 0;
    //high baud rate
    BRGH = 1;
    //RCSTA configuration
    //serial port enable
    SPEN = 1;
    //8 bit receiver
    RX9 = 0;
    //BAUDCON configuration
    //Roll over bit only for auto baud
    // ABDOVF = 0;
    //baud rate generator registers
    BRG16 = 0;
    //baud rate value register - 9600 baud rate
    SPBRG = 129;
    //disable interrupt from UART receiver
    WUE = 0;
    //auto baud detect off
    ABDEN = 0;
    //enable receiver
    CREN = 1;
    //enable transmitter
    TXEN = 1;
}
//read status RCIDL - 1 & TRMT - 1
//enabled in respective functions when using them?

void uart_transmit_char(unsigned char byte) {
    //wait for buffer to be empty
    while (!TXIF);
    //load buffer
    TXREG = byte;
}

void uart_transmit_str(unsigned char *bytes) {
    while (*bytes)
        uart_transmit_char(*(bytes++));
}

unsigned char uart_receive(void){
    //wait for buffer to be full
    while(!RCIF);
    return RCREG;
}
