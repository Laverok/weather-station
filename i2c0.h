#ifndef i2c0_h
#define i2c0_h

#include "MKL46Z4.h"

#define I2C_WRITE	0	// Master write
#define I2C_READ	1	// Master read

#define I2C_WAIT 			while(((I2C0->S & I2C_S_IICIF_MASK) == 0)){}I2C0->S |= I2C_S_IICIF_MASK
#define I2C_TRAN 			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
	
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK
#define I2C_M_STOP		I2C0->C1 &= ~I2C_C1_MST_MASK

#define I2C_M_RESTART I2C0->C1 |= I2C_C1_RSTA_MASK
	
#define I2C_NACK					I2C0->C1 |= I2C_C1_TXAK_MASK
#define I2C_ACK						I2C0->C1 &= ~I2C_C1_TXAK_MASK

void I2C0Init(uint8_t mult, uint8_t icr);
void I2C0WriteRegister(uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t data);
uint8_t I2C0ReadRegister(uint8_t SlaveAddress,uint8_t RegisterAddress);
void I2C0WriteMultRegister(uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t n, uint8_t *data);
void I2C0ReadMultRegister(uint8_t SlaveAddress,uint8_t RegisterAddress,uint8_t n, uint8_t *data);

#endif