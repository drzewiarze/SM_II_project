/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file accelerometer.h
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing enums, structures and declarations for view in LCD screen .
 * @ver 0.1
 */

#ifndef VIEW_H
#define VIEW_H

#include "frdm_bsp.h"
#include "lcd1602.h"
//#include "accelerometer.h"

/**
 * @brief Enum for view in LCD screen settings.
 */
enum ViewType {
    VIEW_X,
    VIEW_Y,
    VIEW_Z
};
/**
 * @brief Initialization views.
 */
void View_Init(void);
/**
 * @brief Updating view based on state.
 * @param view Current view (X, Y, Z).
 */
void View_Update(enum ViewType view);
/**
 * @brief Next view function.
 * @param change view to next
 */
enum ViewType NextView(enum ViewType currentView);

#endif  /* VIEW_H */
