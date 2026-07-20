#include "blackbox.h"

extern uint32_t event_count;
extern unsigned char time[9];
extern unsigned char speed_buffer[3];
extern unsigned char gear_buffer[3];
unsigned char stored_time[10][9];
unsigned char stored_speed_buffer[10][3];
unsigned char stored_gear_buffer[10][3];
extern unsigned char key_pressed;
//Storing events function declaration

void store_time(unsigned char address) {
    for (int i = 0; i < 8; i++)
        write_external_eeprom(address + i, time[i]);
}

void store_speed(unsigned char address) {
    for (int i = 0; i < 2; i++)
        write_external_eeprom(address + i, speed_buffer[i]);
}

void store_gear(unsigned char address) {
    for (int i = 0; i < 2; i++)
        write_external_eeprom(address + i, gear_buffer[i]);
}

void read_time(unsigned char address, unsigned char curr_event) {
    for (int i = 0; i < 8; i++)
        stored_time[curr_event][i] = read_external_eeprom(address + i);
    stored_time[curr_event][8] = '\0';
}

void read_speed(unsigned char address, unsigned char curr_event) {
    for (int i = 0; i < 2; i++)
        stored_speed_buffer[curr_event][i] = read_external_eeprom(address + i);
    stored_speed_buffer[curr_event][2] = '\0';
}

void read_gear(unsigned char address, unsigned char curr_event) {
    for (int i = 0; i < 2; i++)
        stored_gear_buffer[curr_event][i] = read_external_eeprom(address + i);
    stored_gear_buffer[curr_event][2] = '\0';
}
//problem with event count, how do you know array is full or count is actual
//size

void store_event_count(uint32_t num) {
    unsigned char address = 120;
    for (char i = 0; i < 4; i++) {
        write_external_eeprom(address + i, num);
        num >>= 8;
    }
}

void read_event_count(void) {
    unsigned char address = 120;
    event_count = 0;
    for (char i = 0; i < 4; i++) {
        unsigned char byte = read_external_eeprom(address + i);
        event_count |= (byte << (8 * i));
    }
}

void itostr(char *buffer, int num) {
    for (int i = 9; i >= 0; i--) {
        buffer[i] = '0' + num % 10;
        num /= 10;
    }
    buffer[10] = '\0';
}

void event_store(void) {
    unsigned char address = (event_count % 10) * 12;
    event_count++;
    store_time(address);
    store_gear(address + 8);
    store_speed(address + 10);
    store_event_count(event_count);
}

//Reading events function declaration

void event_reader(unsigned char curr_event) {
    for (int i = 0; i < 10; i++) {
        unsigned char address = ((curr_event + i) % 10) * 12;
        read_time(address, i);
        read_gear(address + 8, i);
        read_speed(address + 10, i);
    }
    read_event_count();
}

//View log function declaration
//event reader getting called multiple times, when it only needs to populate data once.

void view_log(void) {
    static unsigned char once = 1;
    clcd_print("LN Time    SP  GR", LINE1(0));
    static unsigned char curr_event;
    if (event_count == 0) {
        clcd_print("No events logged", LINE2(0));
        if (key_pressed == MK_SW12) {
            CLEAR_DISP_SCREEN;
            state = e_main_menu;
            return;
        }
        return;
    }
    int limit = event_count > 10 ? 10 : event_count;
    if (once) {
        event_reader(event_count % 10);
        once = 0;
    }
    clcd_putch('0' + curr_event, LINE2(0));
    clcd_print(stored_time[curr_event], LINE2(2));
    clcd_print(stored_speed_buffer[curr_event], LINE2(14));
    clcd_print(stored_gear_buffer[curr_event], LINE2(11));
    if (key_pressed == MK_SW2 && curr_event < (limit - 1))
        curr_event++;
    else if (key_pressed == MK_SW1 && curr_event > 0)
        curr_event--;
    else if (key_pressed == MK_SW12) {
        CLEAR_DISP_SCREEN;
        once = 1;
        state = e_main_menu;
        return;
    }
}


//Set time function declaration

void set_time(void) {

}

//Download log function _decleration

void download_log(void) {
    static uint16_t delay = 0;
    static unsigned char once = 1;
    if (delay++ == 0) {
        if (once) {
            event_reader(event_count % 10);
            once = 0;
        }
        uart_transmit_str("Log count : \n\r");
        char buffer[11];
        itostr(buffer, event_count);
        uart_transmit_str(buffer);
        uart_transmit_str("\n\rLN TIME     GR SP\n\r");
        unsigned char limit = event_count > 10 ? 10 : event_count;
        for (int i = 0; i < limit; i++) {
            uart_transmit_char('0' + i);
            uart_transmit_str(". ");
            uart_transmit_str(stored_time[i]);
            uart_transmit_char(' ');
            uart_transmit_str(stored_speed_buffer[i]);
            uart_transmit_char(' ');
            uart_transmit_str(stored_gear_buffer[i]);
            uart_transmit_str("\n\r");
        }
        clcd_print("DOWNLOAD SUCCESS", LINE1(0));
    } else if (delay > 3000) {
        delay = 0;
        once = 1;
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }
}

//Clear log function declaration

void clear_log(void) {
    static uint16_t delay = 0;
    event_count = 0;
    if (delay++ == 0) {
        clcd_print("CLEAR SUCCESS", LINE1(0));
        store_event_count(event_count);
    } else if (delay > 3000) {
        delay = 0;
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }
}

