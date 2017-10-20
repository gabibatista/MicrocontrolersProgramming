/*****************************************************
* Programa ativando o PWM
* 
******************************************************/

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>


#include "lab_uino.h"
#include "lcd_usb.h"
#include "funcoes.h"



// programa principal
int main(void)
{
char lcd_buffer[20];
int valor_adc;

	IO_init(); // inicia pinos de IO da placa. 
	lcd_init(LCD_DISP_ON); //inicia o LCD
	lcd_clrscr(); //Limpa tela do LCD
	sprintf(lcd_buffer,"Observe o Led 1 ");
	lcd_puts(lcd_buffer);

	while(1){

		valor_adc=Read_ADC(1);
		lcd_gotoxy(0,1);
		sprintf(lcd_buffer,"ADC_1  = %d ",valor_adc);
		lcd_puts(lcd_buffer);

		Set_PWM_T1C(valor_adc);
		
	}
}
