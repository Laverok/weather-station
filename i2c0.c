#include "i2c0.h"

void I2C0Init(uint8_t mult, uint8_t icr)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;   //ustawienie zegara
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; // clock for I2C
	PORTE->PCR[18] = PORT_PCR_MUX(4);   // SDA
	PORTE->PCR[19] = PORT_PCR_MUX(4);   // SCL
		
	// frequency divider
	I2C0->F |= I2C_F_MULT(mult);
	I2C0->F &= ~I2C_F_ICR_MASK;  
		//I2C_TRAN;   // Transmit Mode Select
	I2C_M_START; 	 	// Master Mode Select
	I2C0->C1 |= I2C_C1_IICEN_MASK;	// I2C Enable
	//I2C0->C1 = 0x80;
	I2C0->FLT |= I2C_FLT_STOPF(0);
	I2C0->FLT |= I2C_FLT_SSIE_MASK;
	I2C0->C1 |=I2C_C1_IICIE_MASK;
	I2C0->C2 |=I2C_C2_HDRS_MASK;
	I2C0->S |= I2C_S_BUSY(0);
	//I2C_TRAN;   // Transmit Mode Select
	//I2C_M_START; 	 	// Master Mode Select

}

void I2C0WriteRegister(uint8_t SlaveAddress, uint8_t RegisterAddress, uint8_t data)
{
	
	I2C_TRAN;
	I2C_M_START;
	
	I2C0->D = ((SlaveAddress << 1) | I2C_WRITE);
	I2C_WAIT;

	I2C0->D = RegisterAddress;
	I2C_WAIT;

	I2C0->D = data;
	I2C_WAIT;

	I2C_M_STOP;

}


uint8_t I2C0ReadRegister(uint8_t SlaveAddress,uint8_t RegisterAddress)
{
	uint8_t data = 0;

	I2C_TRAN;
	I2C_M_START;
	I2C0->D = ((SlaveAddress << 1) | I2C_WRITE);
	I2C_WAIT;

	I2C0->D = RegisterAddress;
	I2C_WAIT;

	I2C0->C1 |= I2C_C1_RSTA_MASK;

	I2C0->D = ((SlaveAddress << 1) | I2C_READ);
	I2C_WAIT;

	I2C_REC	;
	I2C_NACK;

	data = I2C0->D;
	I2C_WAIT;
	
	I2C_M_STOP;
	
	data = I2C0->D;

	return data;
}

void I2C0WriteMultRegister(uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t n, uint8_t *data)
{
	uint8_t i = 0;

	I2C_TRAN;
	I2C_M_START;
	
	I2C0->D =((SlaveAddress << 1) | I2C_WRITE);
	I2C_WAIT;

	I2C0->D =RegisterAddress;
	I2C_WAIT;

	for(i=0; i<n ;i++)
	{
		I2C0->D = *data;
		I2C_WAIT;
		data++;
	}

	I2C_M_STOP;

}


void I2C0ReadMultRegister(uint8_t SlaveAddress,uint8_t RegisterAddress,uint8_t n, uint8_t *data)
{
	uint8_t i = 0;

	I2C_TRAN;
	I2C_M_START;
	
	I2C0->D =((SlaveAddress << 1) | I2C_WRITE);
	I2C_WAIT;

	I2C0->D =RegisterAddress;
	I2C_WAIT;

	I2C_M_RESTART;

	I2C0->D =((SlaveAddress << 1) | I2C_READ);
	I2C_WAIT;

	I2C_REC;
	//I2C_ACK;

	i = I2C0->D;
	I2C_WAIT;

	for(i=0;i<n;i++)
	{
		if (i==(n-1))	I2C_ACK;
		*data = I2C0->D;
		data++;
		I2C_WAIT;
	}

	I2C_M_STOP;

	*data = I2C0->D;
	
}