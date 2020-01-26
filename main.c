#include "MKL46Z4.h"
#include "nucleo.h"
#include "slcd.h"
#include "buttons.h"
#include "weather_interface.h"

void SwitchStateMessage(int state);

int main(void)
{
	int state = 0;
	slcdInitialize();
	buttonsInitialize();
	I2CInitialization();

		while(1){
			
			if(!button1Read()){
				
					if(state < 4){
						state++;
					}
					else{
						state = 0;
					}
					slcdClear();
					SwitchStateMessage(state);
					delay_mc(1000);
			}
			delay_mc(10);
			
			switch(state){
				
				case 0:
					DisplayTemperature();
					break;
				
				case 1:
					DisplayPressure();
					break;
				
				case 2:
					DisplayLight();
					break;
				
				case 3:
					DisplayHumidity();
					break;
				
				default:
					break;
			}
	}

}

void SwitchStateMessage(int state){

		switch(state){
				
				case 0:
					TemperatureMessage();
					break;
				
				case 1:
					PressureMessage();
					break;
				
				case 2:
					LightMessage();
					break;
				
				case 3:
					HumidityMessage();
					break;
				
				default:
					break;
			}
}
