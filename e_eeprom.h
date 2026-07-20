/* 
 * File:   e_eeprom.h
 * Author: bmeno
 *
 * Created on July 14, 2026, 8:07 PM
 */

#ifndef E_EEPROM_H
#define	E_EEPROM_H

#define SLAVE_EEPROM_WRITE 0xA0
#define SLAVE_EEPROM_READ 0xA1

unsigned char read_external_eeprom(unsigned char address);
void write_external_eeprom(unsigned char address,unsigned char data);

#endif	/* E_EEPROM_H */

