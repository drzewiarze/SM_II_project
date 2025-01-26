/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file touchField.h
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing enums, structures and declarations for touch field TSI .
 * @ver 0.1
 */

#ifndef TOUCH_FIELD_H
#define TOUCH_FIELD_H

#include "frdm_bsp.h"
/**
 * @brief Touch field initialization.
 * Sets the appropriate registers and starts the TSI module.
 */
void TouchField_Init(void);
/**
 * @brief Checks if the touch field is touched.
 * @return 1 if the touch field was touched, 0 otherwise.
 */
uint8_t TouchField_IsTouched(void);

#endif /* TOUCH_FIELD_H */
