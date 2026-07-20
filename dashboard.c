/*
 * File:   dashboard.c
 * Author: Poomani Krishna
 *
 * Created on 28 April, 2026, 5:31 PM
 */

#include "blackbox.h"


uint32_t event_count;
uint16_t speed;
unsigned char speed_buffer[3];

unsigned char gear_pos[9] = {'N', 'N', '1', '2', '3', '4', '5', 'R', 'C'};
unsigned char gear;
unsigned char gear_buffer[3];

extern unsigned char key_pressed;
extern State_t state;

void get_gear(void) {
    if (key_pressed == ALL_RELEASED)
        return;
    if (key_pressed != MK_SW3 && gear == 8) {
        gear = 1;
        return;
    }
    if (key_pressed == MK_SW1 && gear < 7)
        gear++;
    else if (key_pressed == MK_SW2 && gear > 1)
        gear--;
    else if (key_pressed == MK_SW3)
        gear = 8;
}

void get_speed(void) {
    speed = read_adc(CHANNEL4);
    speed = ((uint32_t) speed * 99) / 1023;
}

void load_speed_buffer(char *speed_buffer) {
    speed_buffer[0] = '0' + speed / 10;
    speed_buffer[1] = '0' + speed % 10;
    speed_buffer[2] = '\0';
}

void load_gear_buffer(char *gear_buffer) {
    gear_buffer[0] = (gear == 8) ? 'C' : (gear == 0) ? 'O' : 'G';
    gear_buffer[1] = gear_pos[gear];
    gear_buffer[2] = '\0';
}

void view_dashboard(void) {
    clcd_print("Time     GR  SP", LINE1(0));
    static unsigned char prev_gear = 10;

    get_time();
    display_time();

    get_speed();
    load_speed_buffer(speed_buffer);
    clcd_print(speed_buffer, LINE2(13));

    get_gear();
    load_gear_buffer(gear_buffer);
    clcd_print(gear_buffer, LINE2(9));

    if (gear != prev_gear) {
        prev_gear = gear;
        event_store();
    }

    if (key_pressed == MK_SW12) {
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
        return;
    }
}
