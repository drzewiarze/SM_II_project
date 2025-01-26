/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file tsi.h
 * @author Jakub Płoskonka & Koryciak
 * @date styczen 2025
 * @brief File containing enums, structures and declarations.
 * @ver 0.2
 */

#ifndef TSI_H
#define TSI_H

#include "frdm_bsp.h"
/**
 * @brief Touch slider initialization.
 */
void TSI_Init(void);
/**
 * @brief Return value read from the slider (0,100).
 */
uint8_t TSI_ReadSlider (void);
/**
 * @brief Checks if the touch field is touched.
 * @return 1 if the touch field was touched, 0 otherwise.
 */
uint8_t TouchField_IsTouched(void);

#endif /* TSI_H */
