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
 * @brief  Configures the device, sets it to active mode, and enables interrupts.
 */
void Accelerometer_Init(void) {
    uint8_t regValue;

    regValue = Accelerometer_ReadRegister(MMA8451Q_REG_CTRL_REG1);          // Read control register 1
    regValue &= ~0x01;                                                      // Clear ACTIVE bit to put accelerometer in standby mode
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);          // Write back to the register
	
    Accelerometer_WriteRegister(0x2D, 0x01);                                // Enable Data Ready (DRDY) interrupt
    Accelerometer_WriteRegister(0x2E, 0x00);                                // Route DRDY interrupt to INT2 pin
	
    regValue |= 0x01;                                                       // Set ACTIVE bit to start measurements
    Accelerometer_WriteRegister(MMA8451Q_REG_CTRL_REG1, regValue);          // Write back to the register
}
/**
 * @brief Configure interrupt for the INT2 pin (PTA10).
 *        Sets up the PTA10 pin as an input with an interrupt on the rising edge.
 */
void Interrupt_INT2_Pin_PTA10(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;                                     // Enable clock for PORTA
    PORTA->PCR[10] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x9) ;                 // Configure PTA10 for rising-edge interrupt
	PTA->PDDR &= ~(1 << 10);                                                // Set PTA10 as input
    NVIC_EnableIRQ(PORTA_IRQn);                                             // Enable the interrupt in NVIC
}
/**
 * @brief Read accelerometer data.
 * @param data Pointer to a structure to store the accelerometer data (X, Y, Z axes).
 */
void Accelerometer_ReadData(struct accelerometer_data_t *data_XYZ) {
    uint8_t arrayXYZ[6];
    uint8_t status = Accelerometer_ReadRegister(MMA8451Q_REG_STATUS);       // Read status register
	
    if (status) {	
        I2C_ReadRegBlock(MMA8451Q_I2C_ADDRESS, MMA8451Q_REG_OUT_X_MSB, 6, arrayXYZ);

        data_XYZ->x = ((double)((int16_t)((arrayXYZ[0]<<8)|arrayXYZ[1])>>2)/(4096>> MMA8451Q_RANGE_2g)); // Convert 14-bit X data
        data_XYZ->y = ((double)((int16_t)((arrayXYZ[2]<<8)|arrayXYZ[3])>>2)/(4096>> MMA8451Q_RANGE_2g)); // Convert 14-bit Y data
        data_XYZ->z = ((double)((int16_t)((arrayXYZ[4]<<8)|arrayXYZ[5])>>2)/(4096>> MMA8451Q_RANGE_2g)); // Convert 14-bit Z data
    }
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
    I2C_WriteReg(MMA8451Q_I2C_ADDRESS, reg, value);                         // Write value to the register over I2C
}
/**
 * @brief Read a value from a specific register of the accelerometer.
 * @param reg Register address.
 * @return The value read from the register.
 */
uint8_t Accelerometer_ReadRegister(uint8_t reg) {
    uint8_t value;
    I2C_ReadReg(MMA8451Q_I2C_ADDRESS, reg, &value);                         // Read value from the register over I2C
    return value;                                                           // Return the read value
}
