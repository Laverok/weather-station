#include "nucleo.h"

void PressureInitialization()
{
	data[0] = CTRL_REG1;
	I2C0WriteRegister(LPS331,CTRL_REG1_Address,*data);
}


// Puot [mbar]
float ReadPressure()
{
	uint32_t sum; float Pout;
	
	I2C0ReadMultRegister(LPS331,PRESS_OUT_XL,1,data);
	sum = data[0];
	I2C0ReadMultRegister(LPS331,PRESS_OUT_L,1,data);
	sum = sum | (uint16_t)(data[0]<<8);
	I2C0ReadMultRegister(LPS331,PRESS_OUT_H,1,data);
	sum = sum | (uint32_t)(data[0]<<16);
	Pout = (float)sum/4096;
	return Pout;
}

//void TemperatureInitialization(){}
	
float ReadTemperature()
{ float Tout=0.0; uint16_t temp;
	
	I2C0ReadMultRegister(STLM75,TEMP,2,data);
	temp=data[0]>>5|(data[1]<<3);
	if(temp && ((uint16_t)(1<<8)) ==1) 
		Tout=(-0.5)*(float)temp;
	else
		Tout=0.5*(float)temp;
	return Tout;
}

void LightInitialization()
{
	data[0]=PON_AEN	;
	I2C0WriteMultRegister(TSL25721,ALS_ENEBALE,1,data);
	data[0]=ATIME_INTEG_CYCLE;
	I2C0WriteMultRegister(TSL25721,COMMAND_AUTO_INC,1,data);
	cpl=(float)(300*1)/(1*60);
}

float ReadLight()
{
	float Lout=0.0;	uint16_t lightVi; float lux1; float lux2;
	
	I2C0ReadMultRegister(TSL25721,ALS_CH0DATA,2,data);
	lightVi=data[0] | (uint16_t)(data[0]<<8);
	I2C0ReadMultRegister(TSL25721,ALS_CH1DATA,2,data);
	uint16_t lightInf=data[0] | (uint16_t)(data[0]<<8);
	lux1=((float)lightVi-1.87*(float)lightInf)/cpl;
	lux2=((float)lightVi*0.63-(float)lightInf)/cpl;
	//Lout=MAX(lux1,lux2,0)
	if(lux1 >= lux2 && lux1 >= 0)
		Lout=lux1;
  else if(lux2 >= lux1 && lux2 >= 0)
		Lout=lux2;
  else if(0 >= lux1 && 0 >= lux2)
		Lout=0;
  return Lout;
	
}

void HumidityInitialization()
{
	data[0]=CONT_REG1;
	//I2C0WriteMultRegister(HTS221,CONT_REG1_Afdress,1,data);
	
}



