#include "blackbox.h"

extern unsigned char key_pressed;

void display_main_menu() {
    //a flag to keep track of first entry so that first entry into menu starts
    //curr option with 0
    unsigned char menu_options[4][14] = {
        "view logs    ",
        "set time     ",
        "download logs",
        "clear logs   "
    };
    static unsigned char curr_option;

    if (key_pressed == MK_SW2 && curr_option < 3)
        curr_option++;
    else if (key_pressed == MK_SW1 && curr_option > 0)
        curr_option--;
    else if (key_pressed == MK_SW12) {
        CLEAR_DISP_SCREEN;
        state = e_dashboard;
        return;
    }
    else if(key_pressed == MK_SW11){
        switch(curr_option){
            case 0: state = e_view_log; break;
            case 1: state = e_set_time; break;
            case 2: state = e_download_log; break;
            case 3: state = e_clear_log; break;
            default: state = e_main_menu;
        }
        clcd_putch('0' + curr_option, LINE2(13));
        CLEAR_DISP_SCREEN;
        return;
    }
    clcd_print(menu_options[0 + (curr_option & 0x02)], LINE1(3));
    clcd_print(menu_options[1 + (curr_option & 0x02)], LINE2(3));
    if (curr_option & 1) {
        clcd_print("  ", LINE1(0));
        clcd_print("=>", LINE2(0));
    } else {
        clcd_print("=>", LINE1(0));
        clcd_print("  ", LINE2(0));
    }
}
