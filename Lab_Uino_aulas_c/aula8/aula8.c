/*****************************************************
* Programa ativando interrupção timer 0
* 
******************************************************/

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL
#include <util/delay.h>


#include "lab_uino.h"
#include "lcd_usb.h"
#include "funcoes.h"


// programa principal
int main(void)
{
char lcd_buffer[20];
char segundo;

	IO_init(); // inicia pinos de IO da placa. 
	Timer0_init();
	lcd_init(LCD_DISP_ON); //inicia o LCD
	lcd_clrscr(); //Limpa tela do LCD
	sprintf(lcd_buffer,"Temporizando    ");
	lcd_puts(lcd_buffer);
	sei();

	segundo=0;
	tempo[0]=0;
	tempo[1]=0;
	tempo[2]=0;

	while(1){

		if(tempo[0]>200){ //20x 5ms
			tempo[0]=0;
			segundo++;
			lcd_gotoxy(0,1);
			sprintf(lcd_buffer,"tempo= %d ",segundo);
			lcd_puts(lcd_buffer);
		}
		if(tempo[1]>60){
			tempo[1]=0;
			Toggle_D0();
		}
		if(tempo[2]>150){
			tempo[2]=0;
			Toggle_D1();
		}

	}
}
