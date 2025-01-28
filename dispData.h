/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file dispData.h
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing enums, structures and declarations for displaying data in LCD screen.
 * @ver 0.1
 */

#ifndef VIEW_H
#define VIEW_H

#include "lcd1602.h"
#include "accelerometer.h"

/**
 * @brief The `Axis` enum defines the symbolic names for the X, Y, and Z axes, used to represent the currently displayed axis in the program.
 */
enum Axis {
     AXIS_X,    //axis x
     AXIS_Y,    //axis y
     AXIS_Z     //axis z
};
/**
 * @brief The `display_progress_bar` function displays a dynamic progress bar on the LCD display, 
 * visualizing `acceleration` as the filling of the bar relative to the center, 
 * distinguishing between positive (right) and negative (left) directions.
 * @param acceleration A float value representing the acceleration. 
 */
void display_progress_bar(float acceleration);
/**
 * @brief The function updates the LCD display with text and a progress bar based on the acceleration value if the data has changed.
 * @param text_from_display_buffer A pointer to a string representing the text on the first line of the LCD display;
 * @param acceleration A float value representing the acceleration.
 */
void update_lcd_with_progress_bar(const char *text_from_display_buffer, float acceleration);
/**
 * @brief The function handles touch slider taps by cyclically switching the currently displayed axis (X → Y → Z → X) each time a tap is detected.
 * @param current_axis A pointer to a variable of type `enum Axis` representing the currently displayed axis (X, Y or Z).
 */
void handle_touch_input(enum Axis *current_axis);

#endif  /* VIEW_H */
