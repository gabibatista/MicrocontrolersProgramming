/*****************************************************
* Programa helo lcd
* 
******************************************************/

// inclui arquivos de definições da biblioteca
#include <avr/io.h>
#include <stdio.h>

// define xtal da CPU para rotinas de delay.
#define F_CPU 8000000UL
#include <util/delay.h>


// inclui arquivos e definições da placa
#include "lab_uino.h"

// inclui funcões do LCD
#include "lcd_usb.h"


//define funções e rotinas
void IO_init(void){
	DDRB = (1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1);
	DDRC = (1<<6)|(1<<7);
	DDRD = (1<<4)|(1<<6)|(1<<7);
	DDRE = 0;
	DDRF = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = (1<<5)|(1<<1)|(1<<0);
	PORTE = (1<<2);
	PORTF = (1<<7)|(1<<6);
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD); //desliga interface JTAG.
}


// programa principal
int main(void)
{
char lcd_buffer[20];
char x;

	IO_init(); // inicia pinos de IO da placa. 
	lcd_init(LCD_DISP_ON); //inicia o LCD
	lcd_clrscr(); //Limpa tela do LCD


	sprintf(lcd_buffer,"LCD ativado     ");
	lcd_puts(lcd_buffer);
	lcd_gotoxy(0,1);
	sprintf(lcd_buffer,"aperte ack      ");
	lcd_puts(lcd_buffer);

	x=0;
	
	while(1){

		if(Ch_busy_lig){
			x--;
			lcd_gotoxy(0,0);
			sprintf(lcd_buffer,"x= %d       ",x);
			lcd_puts(lcd_buffer);
			lcd_gotoxy(0,1);
			sprintf(lcd_buffer,"aperte ack +   ");
			lcd_puts(lcd_buffer);
		}

		if(Ch_ack_lig){
			x++;
			lcd_gotoxy(0,0);
			sprintf(lcd_buffer,"x= %d       ",x);
			lcd_puts(lcd_buffer);
			lcd_gotoxy(0,1);
			sprintf(lcd_buffer,"aperte busy -  ");
			lcd_puts(lcd_buffer);
		}

		_delay_ms(500);
	}
}
