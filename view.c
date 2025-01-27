/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file accelerometer.c
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing definitions for view in LCD screen.
 * @ver 0.1
 */

#include "view.h"
#include "accelerometer.h"
#include <stdio.h>


char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};


/******************************************************************************\
* Functions
\******************************************************************************/
/**
 * @brief View initialization function.
 */
void View_Init(void) {
    LCD1602_ClearAll();
}
/**
 * @brief View update function.
 * @param view Selected view (VIEW_X, VIEW_Y, VIEW_Z)
 */
void View_Update(enum ViewType view) {
		struct accelerometer_data_t data;
    Accelerometer_ReadData(&data);
    LCD1602_ClearAll();

    switch (view) {
    case VIEW_X:
        LCD1602_SetCursor(0, 0);
        sprintf(display,"Axis X: %+4.2f g",data.x);	// Przyspieszenie w osi X
		LCD1602_Print(display);
        break;

    case VIEW_Y:
        LCD1602_SetCursor(0, 0);
        sprintf(display,"Axis Y: %+4.2f g",data.y);	// Przyspieszenie w osi Y
		LCD1602_Print(display);
        
        break;

    case VIEW_Z:
        LCD1602_SetCursor(0, 0);
        sprintf(display,"Axis Z: %+4.2f g",data.z);	// Przyspieszenie w osi z
		LCD1602_Print(display);
        break;
    }
}
/**
 * @brief Next view function.
 * @param change view to next
 */
enum ViewType NextView(enum ViewType currentView) {
    switch (currentView) {
        case VIEW_X: return VIEW_Y;
        case VIEW_Y: return VIEW_Z;
        case VIEW_Z: return VIEW_X;
        default: return VIEW_X; // Domyślny widok na wypadek błędu
    }
}
