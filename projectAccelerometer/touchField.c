/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file touchField.c
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing enums, structures and declarations for touch field TSI.
 * @ver 0.1
 */

#include "tsi.h"
#include "touchField.h"

/******************************************************************************\
* Private memory declarations
\******************************************************************************/
/**
 * Flag indicating whether the touch field is touched.
 */
static uint8_t touchFieldFlag = 0;
/**
 * @brief TSI interrupt service function.
 * Supports touch input on the touch field.
 */
void TSI0_IRQHandler(void) {
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;     //  Clear scan end flag
    change_electrode();                     //  Switching electrodes and updating data

    // Check if any electrode has been touched
    if (gu16Delta[0] > gu16Threshold[0] || gu16Delta[1] > gu16Threshold[1]) {
        touchFieldFlag = 1; // Touching the field
    } else {
        touchFieldFlag = 0; // No touch
    }
}
/**
 * @brief Touch field initialization.
 */
void TouchField_Init(void) {
    TSI_Init(); // Calling an existing function to initialize the TSI module
}
/**
 * @brief Checks if the touch field is touched.
 * @return 1 if the touch field was touched, 0 otherwise.
 */
uint8_t TouchField_IsTouched(void) {
    return touchFieldFlag;
}