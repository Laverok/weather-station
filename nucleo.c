#include "nucleo.h"

// Initializes and reads from a pressure sensor, the result is in mBars
uint32_t ReadPressure(void)
{
		uint32_t pres = 0;
		uint8_t meas1 = 0, meas2 = 0, meas3 = 0;
	
		i2c_write_byte(LPS331, CTRL_REG1_Address, CTRL_REG1); // Pressure sensor initialization
		delay_mc(100);
	
		meas1 = i2c_read_byte(LPS331 , PRESS_OUT_XL|(1<<7));
		delay_mc(100);
		meas2 = i2c_read_byte(LPS331 , PRESS_OUT_L|(1<<7));
		delay_mc(100);
		meas3 = i2c_read_byte(LPS331 , PRESS_OUT_H|(1<<7));
	
		pres = meas1 + ((uint16_t)meas2<<8) + ((uint16_t)meas3<<16);
		pres = pres/4096;
	
		return pres;
} 

// Reads from a temperature sensor, the result is an integer (Celsius degrees)
uint16_t ReadTemperature(void)
{		
		uint16_t temp = 0;
		temp = i2c_read_byte(STLM75, TEMP);
		return temp;
}

// Initializes and reads from a humidity sensor, the result is in %Rh
uint32_t ReadHumidity()
{
	float HrH0=0.0,HrH1=0.0, HlsbL0=0.0, HlsbL1=0.0,  HlsbL= 0.0, HlsbH=0.0, HlsbH0=0.0, HlsbH1=0.0; // Parameters used for interpolation
	float hum0=0.0, hum1=0.0; // Measurements (H = high byte, L = low byte)
	uint16_t hum=0,HrH=0,Hlsb=0; // Parameters combined into 16bit integers
	uint32_t humidity = 0; // Result
	
	i2c_write_byte(HTS221, CONT_REG1_Address, CONT_REG1); // Humidity sensor initialization
	delay_mc(10);
	
	//Read calibration variables
	HrH0 = (i2c_read_byte(HTS221,H0_rH_x2))/2;
	delay_mc(10);
	HrH1 = (i2c_read_byte(HTS221,H1_rH_x2))/2;
	delay_mc(10);
	HlsbL0 = i2c_read_byte(HTS221,H0_T0_OUT);
	delay_mc(10);
	HlsbL1 = i2c_read_byte(HTS221,H0_T0_OUT | 0x01);
	delay_mc(10);
	HlsbH0 = i2c_read_byte(HTS221,H1_T0_OUT);
	delay_mc(10);
	HlsbH1 = i2c_read_byte(HTS221,H1_T0_OUT | 0x01);
	delay_mc(10);
	hum0 = i2c_read_byte(HTS221,HUMIDITY_OUT_L |(1<<7));
	delay_mc(10);
	hum1 = i2c_read_byte(HTS221,HUMIDITY_OUT_H | (1<<7));
	delay_mc(10);
	HlsbL = (uint16_t)HlsbL0 | (uint16_t)HlsbL1<<8;
	HlsbH = (uint16_t)HlsbH0 | (uint16_t)HlsbH1<<8;
	hum = (uint16_t)hum0 | (uint16_t)hum1<<8;
	
	humidity = (HrH1 - HrH0) * (hum - HlsbL) / (HlsbH - HlsbL) + HrH0;
	
	return humidity;
}

uint32_t ReadLight(void)
{
	float lux1 = 0.0, lux2 = 0.0, cpl = 0.0;
  float lightViL=0,lightViH=0,lightInfL=0,lightInfH=0;
	uint16_t lightVi=0, lightInf=0;
	uint32_t Lout = 0;
	
	i2c_write_byte(TSL25721, ALS_ENABLE | 0x80, ALS_AEN | ALS_PON);	 
	delay_mc(10);
	i2c_write_byte(TSL25721, ALS_TIME | 0x80, ALS_ATIME);	
	delay_mc(10);

	cpl=(101/60); // (ATIME_MS * AGAINX) / (GA * 60)
	
	lightViL=i2c_read_byte(TSL25721,ALS_C0DATA|(1<<7));
	delay_mc(10);
	lightViH=i2c_read_byte(TSL25721,ALS_C0DATAH|(1<<7));
	delay_mc(10);
	lightVi=(uint8_t)lightViL | ((uint8_t)lightViH<<8);
	lightInfL=i2c_read_byte(TSL25721,ALS_C1DATA|(1<<7));
	delay_mc(10);
	lightInfH=i2c_read_byte(TSL25721,ALS_C1DATAH|(1<<7));
	delay_mc(10);
	lightInf=(uint8_t)lightInfL | (uint8_t)lightInfH<<8;
	lux1=((float)lightVi-1.87*(float)lightInf)/cpl;
	lux2=((float)lightVi*0.63-(float)lightInf)/cpl;
	
	// Returns maximum value between lux1 and lux2
	if(lux1 >= lux2)
	{Lout=lux1;}
  else if(lux2 >= lux1)
	{Lout=lux2;}
	
  return Lout;
}

