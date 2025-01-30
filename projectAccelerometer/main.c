#include "accelerometer.h"
#include "dispData.h"
#include "tsi.h"
#include "lcd1602.h"
#include "frdm_bsp.h"
#include "MKL05Z4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

volatile uint8_t odczytaj_dane_flaga = 0;                   // Flag in interrupt handling
struct accelerometer_data_t acc_data;                       // Structure to store accelerometer data defined in accelerometer.h

void PORTA_IRQHandler(void) {
    if (PORTA->ISFR & (1 << 10)) {                          // Check if the interrupt was triggered by pin PTA10
        PORTA->ISFR |= (1 << 10);                           // Clear the interrupt flag for pin PTA10 by writing '1' to the corresponding bit
        odczytaj_dane_flaga = 1;                            // Set the flag to indicate that new data is available
    }
}

int main(void) {
    char display[17] = {0x20};                              // Initialize the array to 16 characters + '\0'
    enum Axis current_axis = AXIS_X;                        // Default axis is X

    Interrupt_INT2_Pin_PTA10();                                                       
    Accelerometer_Init();                                   // Initializations MMA8451Q
    LCD1602_Init();                                         // Initializations LCD
    TSI_Init();                                             // Initializations Touch Panel

    while (1) {
			
	if (odczytaj_dane_flaga ) {                         		// Check if new data is available
        odczytaj_dane_flaga = 0;                            		// Reset the data ready flag
			
    	handle_touch_input(&current_axis);                      	// Handle touch input to change the current axis
	Accelerometer_ReadData(&acc_data);                      	// Reading data from the accelerometer
    	switch (current_axis) {                                 	// Displaying data for the selected axis
        	case AXIS_X:
            	sprintf(display, "Axis X: %+4.2f g", acc_data.x);   	// Format and display data for axis X
            	update_lcd_with_progress_bar(display, acc_data.x);  	// Update LCD with axis X data and progress bar
            	break;
        	case AXIS_Y:
            	sprintf(display, "Axis Y: %+4.2f g", acc_data.y);   	// Format and display data for axis Y
            	update_lcd_with_progress_bar(display, acc_data.y);  	// Update LCD with axis Y data and progress bar
            	break;
        	case AXIS_Z:
            	sprintf(display, "Axis Z: %+4.2f g", acc_data.z);   	// Format and display data for axis Z
            	update_lcd_with_progress_bar(display, acc_data.z);  	// Update LCD with axis Z data and progress bar
            	break;
    	}
    }
}
