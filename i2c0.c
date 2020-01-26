#include "MKL46Z4.h"     
#include "i2c0.h"

void i2c_start()
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

 void I2CInitialization()
{
	uint8_t temp;
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
  SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK);

	PORTC->PCR[1] = PORT_PCR_MUX(2);  
	PORTC->PCR[2] = PORT_PCR_MUX(2);  
	
	//	I2C baud rate = bus speed (Hz)/(mul × SCL divider)
	//	bus speed (Hz) = 21000000000
	//	ICR = 14 => SCL = 56		mul = 4
	//	set to 93,75k baud

 	I2C1->F = (I2C_F_ICR(14));
		
	//enable i2c and set to master mode
	I2C1->C1 |= (I2C_C1_IICEN_MASK);
	I2C1->C1 |= (I2C_C1_IICIE_MASK);
	
	// Select high drive mode
	I2C1->C2 |= (I2C_C2_HDRS_MASK);
}  


void i2c_wait(void) {
	while((I2C1->S & I2C_S_IICIF_MASK)==0) {
	} 
  I2C1->S |=I2C_S_IICIF_MASK;
}

void i2c_read_setup(uint8_t dev, uint8_t address)
{
	i2c_start();							/*set to transmit mode */
	I2C1->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */
	I2C_TRAN;
	I2C1->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */
	I2C_M_RSTART;				   /*repeated start */
	I2C1->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */
	I2C_REC;						   /*set to receive mode */

}


//////////funcs for reading and writing a single byte
//using 7bit addressing reads a byte from dev:address
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;
	i2c_start();							/*set to transmit mode */
	I2C1->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */
	
	I2C1->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */
		
	I2C_M_RSTART;				   /*repeated start */
	I2C1->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */
	
	I2C_REC;						   /*set to recieve mode */
	NACK;									 /*set NACK after read	*/
	
	data = I2C1->D;					/*dummy read	*/
	I2C_WAIT								/*wait for completion */
	
	I2C_M_STOP;							/*send stop	*/
	data = I2C1->D;					/*read data	*/

	return data;
}



//using 7bit addressing writes a byte data to dev:address
#pragma no_inline 
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{
	
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C1->D = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */
	
	I2C1->D =  address;		/*send write address	*/
	I2C_WAIT
		
	I2C1->D = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;
}


