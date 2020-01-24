#ifndef nucleo_h
#define nucleo_h

#include "MKL46Z4.h"
#include "i2c0.h"

//slave address for devices

#define STLM75 							0x49 				// Digital temperature sensor
#define LPS331 							0x5D 				// MEMS pressure sensor -- WHO_AM_I register
#define TSL25721						0x39 				// Light to digital converter
#define HTS221							0x5F 				// Capacitove digital sensor for relative humidity

//Pressure define
#define CTRL_REG1 					0x92  // Power Mode on, 25Hz Pressure Table18 ODR2=1 ODR1&ODR0=0
#define CTRL_REG1_Address 	0x20 				// Control register address
#define PRESS_OUT_XL 				0x28				// Pressure out 1B [001]
#define PRESS_OUT_L 				0x29				// Pressure out 1B [010]
#define PRESS_OUT_H					0x2A				// Pressure out 1B [100]

//Temperature define
#define TEMP 								0x00				// Temperature reading register

//Lght define
#define ATIME_INTEG_CYCLE 	0x92				// 300ms
#define ALS_CH0DATA					0x14
#define ALS_CH0DATAH				0x15
#define ALS_CH1DATA					0x16
#define ALS_CH1DATAH				0x17
//#define CONFIGURATION_ALS		0x0D				// configuration register
#define PON_AEN							0b00000011	// power on & ALS enable
#define ALS_ENEBALE					0x00
#define COMMAND_AUTO_INC		0b10100000	//

//Humidity define
#define CONT_REG1_Address		0x20				// control register1 address
#define CONT_REG1						0x83        // Power mode on, 12,5Hz Table 17			
#define HUMIDITY_OUT_L			0x28				// out addres data 1B
#define HUMIDITY_OUT_H			0x29				// out addres data 1B
#define H0_rH_x2						0x30				// humidity coefficients address 1B
#define H1_rH_x2						0x31
#define H0_T0_OUT						0x36				// humidity LSB output address 2B
#define H1_T0_OUT						0x3A

static uint8_t data[4];
static float cpl;

void TemperatureInitialization();
void PressureInitialization();
void LightInitialization();
void HumidityInitialization();

float ReadPressure();
float ReadTemperature();
float ReadLight();
float ReadHumidity();



#endif