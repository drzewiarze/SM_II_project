/******************************************************************************
 * This file is part of the Microprocessor Systems II project.                *                                                 *
 ******************************************************************************/

/**
 * @file accelerometer.c
 * @author Jakub Płoskonka
 * @date styczen 2025
 * @brief File containing definitions for accelerometer MMA8451Q.
 * @ver 0.2
 */

#include "accelerometer.h"

/******************************************************************************\
* Private prototypes
\******************************************************************************/
void Accelerometer_WriteRegister(uint8_t reg, uint8_t value);
uint8_t Accelerometer_ReadRegister(uint8_t reg);
/******************************************************************************\
* Functions
\******************************************************************************/
/**
 * @brief Initialize the accelerometer.
 */
void Accelerometer_Init(void) {
    uint8_t regValue;

    regValue = Accelerometer_ReadRegister(MMA8451Q_REG_CTRL_REG1);
    regValue &= ~0x01; // Clear ACTIVE bit to put accelerometer in standby mode
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);

    Accelerometer_SetRange(MMA8451Q_RANGE_2g); // Set default range to ±2g

    regValue |= 0x01; // Set ACTIVE bit to start measurements
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);
}
/**
 * @brief Set the range of the accelerometer.
 * @param range The range to set (2g, 4g, 8g).
 */
void Accelerometer_SetRange(mma8451q_range_t range) {
    uint8_t regValue;

    regValue = Accelerometer_ReadRegister(MMA8451Q_REG_CTRL_REG1);
    regValue &= ~0x01; // Put accelerometer in standby mode
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);

    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG2, range); // Set range

    regValue |= 0x01; // Reactivate accelerometer
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);
}
/**
 * @brief Read accelerometer data.
 * @param data Pointer to structure to store the data.
 */
void Accelerometer_ReadData(void) {
    uint8_t buffer[6];
    double x,y,z;


    I2C_ReadRegBlock(MMA8451Q_I2C_ADDRESS, MMA8451Q_REG_OUT_X_MSB, 6, buffer);

    switch (Accelerometer_ReadRegister(MMA8451Q_REG_CTRL_REG2) & 0x03)

    x = (double)(int16_t)((buffer[0] << 8) | buffer[1]) >> 2; // Convert 14-bit X data
    y = (double)(int16_t)((buffer[2] << 8) | buffer[3]) >> 2; // Convert 14-bit Y data
    z = (double)(int16_t)((buffer[4] << 8) | buffer[5]) >> 2; // Convert 14-bit Z data
}
/**
 * @brief Configure interrupt for INT2 pin.
 * @param enable Enable or disable interrupt.
 */
void Accelerometer_ConfigureINT2(uint8_t enable) {
    uint8_t regValue;

    regValue = Accelerometer_ReadRegister(MMA8451Q_REG_CTRL_REG1);
    if (enable) {
        regValue |= (1 << 2); // Enable interrupt on INT2
    } else {
        regValue &= ~(1 << 2); // Disable interrupt
    }
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);
}
/**
 * @brief Check interrupt source.
 * @return Interrupt source register value.
 */
uint8_t Accelerometer_GetInterruptSource(void) {
    return Accelerometer_ReadRegister(MMA8451Q_REG_INT_SOURCE);
}
/******************************************************************************\
* Private functions
\******************************************************************************/
/**
 * @brief Write value to a specific register of the accelerometer.
 * @param reg Register address.
 * @param value Value to write.
 */
void Accelerometer_WriteRegister(uint8_t reg, uint8_t value) {
    I2C_WriteReg(MMA8451Q_I2C_ADDRESS, reg, value);
}
/**
 * @brief Read value from a specific register of the accelerometer.
 * @param reg Register address.
 * @return Value read from the register.
 */
uint8_t Accelerometer_ReadRegister(uint8_t reg) {
    uint8_t value;
    I2C_ReadReg(MMA8451Q_I2C_ADDRESS, reg, &value);
    return value;
}
