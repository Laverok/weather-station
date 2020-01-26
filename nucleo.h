#ifndef nucleo_h
#define nucleo_h

#include "MKL46Z4.h"
#include "i2c0.h"
#include "extra.h"
#include "math.h"

//slave address for devices

#define STLM75 							0x90 				// Digital temperature sensor
#define LPS331 							0xBA 				// MEMS pressure sensor -- WHO_AM_I register
#define TSL25721						0x72 				// Light to digital converter
#define HTS221							0xBE 				// Capacitive digital sensor for relative humidity

//Pressure define
#define CTRL_REG1 					0b11100000  // Power Mode on, 25Hz Pressure Table18 ODR2=1 ODR1&ODR0=0
#define CTRL_REG1_Address 	0x20 				// Control register address
#define PRESS_OUT_XL 				0x28				// Pressure out 1B [001]
#define PRESS_OUT_L 				0x29				// Pressure out 1B [010]
#define PRESS_OUT_H					0x2A				// Pressure out 1B [100]

//Temperature define
#define TEMP 								0x00				// Temperature reading register

//Light define
#define ALS_C0DATA				 	0x14				// CH0 ADC low data register
#define ALS_C0DATAH				  0x15				// CH0 ADC high data register
#define ALS_C1DATA					0x16				// CH1 ADC low data register
#define ALS_C1DATAH				  0x17				// CH1 ADC high data register
#define ALS_ENABLE					0x00				// ALS Enable register
#define ALS_TIME						0x01				// ALS Time register
#define ALS_AEN							0x02				// ALS Enable
#define ALS_PON							0x01				// Power ON
#define ALS_ATIME						0xDB				// integ cycles = 37, time = 101ms

//Humidity define
#define CONT_REG1_Address		0x20				// control register1 address
#define CONT_REG1						0x85        // Power mode on, 12,5Hz Table 17			
#define HUMIDITY_OUT_L			0x28				// out addres data 1B
#define HUMIDITY_OUT_H			0x29				// out addres data 1B
#define H0_rH_x2						0x30				// humidity coefficients address 1B
#define H1_rH_x2						0x31
#define H0_T0_OUT						0x36				// humidity LSB output address 2B
#define H1_T0_OUT						0x3A

static float cpl;

uint32_t ReadPressure(void);
uint16_t ReadTemperature(void);
uint32_t ReadLight(void);
uint32_t ReadHumidity(void);

#endif
