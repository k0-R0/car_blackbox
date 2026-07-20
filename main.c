/*
 * File:   main.c
 * Author: Poomani Krishna
 *
 * Created on 28 April, 2026, 5:29 PM
 */

#include "blackbox.h"

State_t state;

unsigned char key_pressed;
extern uint32_t event_count;

void init_config() {
    state = e_dashboard;
    init_clcd();
    init_i2c();
    init_ds1307();
    init_adc();
    init_matrix_keypad();
    init_uart();
}

void main(void) {
    init_config();
    read_event_count();
    while (1) {
        // Detect key press
        key_pressed = read_switches(STATE_CHANGE);
        switch (state) {
            case e_dashboard:
                // Display dashboard
                view_dashboard();
                break;

            case e_main_menu:
                // Display dashboard
                display_main_menu();
                break;

            case e_view_log:
                // Display dashboard
                view_log();
                break;

            case e_download_log:
                download_log();
                break;

            case e_clear_log:
                clear_log();
                break;


            case e_set_time:
                set_time();
                break;

        }

    }

}