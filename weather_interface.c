#include "weather_interface.h"

void DisplayTemperature(void)
{
	uint16_t temp = 0;
	
	temp = ReadTemperature();
	slcdDisplay(temp, 10);
}

void DisplayPressure(void){
	uint16_t pressure = 0;
	
	pressure = ReadPressure();
	slcdDisplay(pressure, 10);
}

void DisplayLight(void){
	uint16_t light = 0;
	
	light = ReadLight();
	slcdDisplay(light, 10);
}

void DisplayHumidity(void){
	uint16_t humidity = 0;
	
	humidity = ReadHumidity();
	slcdDisplay(humidity, 10);
}

void TemperatureMessage(void){
	
	LCD->WF8B[LCD_Front_Pin[((2*1)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F | LCD_S_G);
}

void PressureMessage(void){
	
	LCD->WF8B[LCD_Front_Pin[((2*1)-2)]] = (LCD_S_E | LCD_S_F | LCD_S_G);
	LCD->WF8B[LCD_Front_Pin[((2*1)-1)]] = (LCD_S_A | LCD_S_B);
}

void LightMessage(void){
	
	LCD->WF8B[LCD_Front_Pin[((2*1)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F);
}

void HumidityMessage(void){
	
	LCD->WF8B[LCD_Front_Pin[((2*1)-2)]] = (LCD_S_E | LCD_S_F | LCD_S_G);
	LCD->WF8B[LCD_Front_Pin[((2*1)-1)]] = (LCD_S_B | LCD_S_C);
}
