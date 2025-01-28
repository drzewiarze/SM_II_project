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
    regValue |= 0x01; // Set ACTIVE bit to start measurements
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);
}
/**
 * @brief Read accelerometer data.
 * @param data Pointer to structure to store the data.
 */
void Accelerometer_ReadData(struct accelerometer_data_t *ACC_DATA) {
    uint8_t arrayXYZ[6];
    
    I2C_ReadRegBlock(MMA8451Q_I2C_ADDRESS, MMA8451Q_REG_OUT_X_MSB, 6, arrayXYZ);

    ACC_DATA->x = ((double)((int16_t)((arrayXYZ[0]<<8)|arrayXYZ[1])>>2)/(4096>> MMA8451Q_RANGE_2g)); // Convert 14-bit X data
    ACC_DATA->y = ((double)((int16_t)((arrayXYZ[2]<<8)|arrayXYZ[3])>>2)/(4096>> MMA8451Q_RANGE_2g)); // Convert 14-bit Y data
    ACC_DATA->z = ((double)((int16_t)((arrayXYZ[4]<<8)|arrayXYZ[5])>>2)/(4096>> MMA8451Q_RANGE_2g)); // Convert 14-bit Z data
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
