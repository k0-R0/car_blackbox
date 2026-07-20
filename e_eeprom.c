#include "blackbox.h"

void write_external_eeprom(unsigned char address, unsigned char data){
    i2c_start();
    i2c_write(SLAVE_EEPROM_WRITE);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
    //blocking delay for external eeprom write to finish
    //clock stretch???
    for(int i = 3000; i--; );
}

unsigned char read_external_eeprom(unsigned char address){
    i2c_start();
    i2c_write(SLAVE_EEPROM_WRITE);
    i2c_write(address);
    i2c_rep_start();
    i2c_write(SLAVE_EEPROM_READ);
    unsigned char data = i2c_read();
    i2c_stop();
    return data;
}