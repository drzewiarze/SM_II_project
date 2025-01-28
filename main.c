#include "accelerometer.h"
#include "dispData.h"
#include "tsi.h"
#include "lcd1602.h"
#include "frdm_bsp.h"
#include "MKL05Z4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct accelerometer_data_t acc_data;

int main(void) {
    char display[17] = {0x20};                              // Initialize the array to 16 characters + '\0'
    enum Axis current_axis = AXIS_X;                        // Default axis

                                                            
    LCD1602_Init();                                         // Initializations LCD
    Accelerometer_Init();                                   // Initializations MMA8451Q
    TSI_Init();                                             // Initializations Touch Panel

    while (1) {
    Accelerometer_ReadData(&acc_data);                          // Reading data from the accelerometer

    handle_touch_input(&current_axis);                      // Axis change handling

    switch (current_axis) {                                 // Displaying data for the selected axis
        case AXIS_X:
            sprintf(display, "Axis X: %+4.2f g", acc_data.x);
            update_lcd_with_progress_bar(display, acc_data.x);
            break;
        case AXIS_Y:
            sprintf(display, "Axis Y: %+4.2f g", acc_data.y);
            update_lcd_with_progress_bar(display, acc_data.y);
            break;
        case AXIS_Z:
            sprintf(display, "Axis Z: %+4.2f g", acc_data.z);
            update_lcd_with_progress_bar(display, acc_data.z);
            break;
    }

    DELAY(1000);                                            // better for the eye
}
}
