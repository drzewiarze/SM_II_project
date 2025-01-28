/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file dispData.c
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing definitions for displaying data in LCD screen.
 * @ver 0.1
 */

#include "dispData.h"
#include "accelerometer.h"
#include "tsi.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************\
* Functions
\******************************************************************************/
/**
 * @brief The `display_progress_bar` function displays a dynamic progress bar on the LCD display, 
 * visualizing `value` as the filling of the bar relative to the center, 
 * distinguishing between positive (right) and negative (left) directions.
 * @param acceleration A float value representing the acceleration.
 */
void display_progress_bar(float acceleration) {
    static char bar[17]; 							// 16 display columns and the terminating character "/0"
    int center_point = 7; 							// Center point of the diy
    int points_on_the_bar = acceleration * 8; 		// Scaling points on the LCD display bar relative to acceleration [8 left and 8 right]

    memset(bar, ' ', sizeof(bar) - 1); 				// Cleaning the points on the bar [ptr to memory, entered data, number of bytes replaced   ]

    if (points_on_the_bar >= 0) {
        for (int i = 0; i <= points_on_the_bar; i++) {
            bar[center_point + i] = 'o'; 			// Filling the "o" to the right of the center
        }
    } else {
        for (int i = 0; i >= points_on_the_bar; i--) {
            bar[center_point + i] = 'o'; 			// Filling the "o" to the left of the center
        }
    }

    LCD1602_SetCursor(0, 1);        				// Set the cursor to the beginning of the second line
    LCD1602_Print(bar);            					// Displayng the bar 
}
/**
 * @brief The function updates the LCD display with text and a progress bar based on the acceleration value if the data has changed.
 * @param text_from_display_buffer A pointer to a string representing the text on the first line of the LCD display;
 * @param acceleration A float value representing the acceleration.
 */
void update_lcd_with_progress_bar(const char *text_from_display_buffer, float acceleration) {
    static char previous_text[17];                          // Previous string buffer
    char temporary_text[17];
    strncpy(temporary_text, text_from_display_buffer, 16);  // Copying data to temporary buffer

    if (strcmp(temporary_text, previous_text) != 0) {       // Update displayed data if it has changed
        LCD1602_SetCursor(0, 0); 
        LCD1602_Print(temporary_text);
        strncpy(previous_text, temporary_text, 16);         // Buffer update
    }

    display_progress_bar(acceleration);                     // Displaying the progress bar
}
/**
 * @brief The function handles touch slider taps by cyclically switching the currently displayed axis (X → Y → Z → X) each time a tap is detected.
 * @param current_axis A pointer to a variable of type `enum Axis` representing the currently displayed axis (X, Y or Z).
 */
void handle_touch_input(enum Axis *current_axis) {
    static uint8_t was_touched_flag = 0;                    // Touch flag

    if (TSI_ReadSlider() > 0 && !was_touched_flag) {        // Wykrycie dotkniecia
        *current_axis = (*current_axis + 1) % 3;            // Switching axes (X -> Y -> Z -> X) [%3 means max 3 positions]
        was_touched_flag = 1;                               // Set the touch flag
    } else {
        was_touched_flag = 0;                               // Reset flag when no touch
    }
}
