#include "MKL46Z4.h"
//#include "i2c0.h"
#include "nucleo.h"
#include "slcd.h"

int main(void)
{
	float pressure;
	
	slcdInitialize();
	I2C0Init(2, 0);
	
	//PressureInitialization();
	//LightInitialization();
	
	while(1){
		//slcdDisplay(20, 10);
		pressure = ReadTemperature();
		slcdDisplay((uint16_t)pressure, 10);
		
	}
}
