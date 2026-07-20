/* 
 * File:   black_box.h
 * Author: Poomani Krishna
 *
 * Created on 28 April, 2026, 5:32 PM
 */

#ifndef BLACK_BOX_H
#define	BLACK_BOX_H

#include <xc.h>
#include <stdint.h>

#include "e_eeprom.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "i2c.h"
#include "ds1307.h"
#include "clcd.h"
#include "adc.h"
#include "uart.h"

/* Enum for maintaining the app state */
typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
} State_t;


extern State_t state; // App state

//Function declarations

//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(void);


//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(unsigned char );

//Set time function declaration
void set_time(void);

//Download log function _decleration
void download_log(void);

//Clear log function declaration
void clear_log(void);

//read event count stored in External EEPROM
void read_event_count(void);
#endif	/* BLACK_BOX_H */