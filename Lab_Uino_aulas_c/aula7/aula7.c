/*****************************************************
* Programa interface serial
* 
******************************************************/

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>

#include "lab_uino.h"
#include "lcd_usb.h"
#include "funcoes.h"


//***************************
// Inicia USART 
//***************************
void USART_init(void)
{
    UBRR1 = 51;                    // define baud rate e habilita a USART
    UCSR1B = (1<<TXEN1) | (1<<RXEN1);
}

//****************************
// Transmite um byte
//****************************
void USART_Send( unsigned char data )
{
    while( !(UCSR1A & (1<<UDRE1)) ); // aguarda buffer de transmissão vazio
    UDR1 = data;                     // envia o byte
}

#define tem_caracter (UCSR1A & (1<<RXC1))

//***************************
// Receive one byte
//***************************
unsigned char USART_Get(void)
{
    while( !(UCSR1A & (1<<RXC1)) ); //aguarda receber um  byte
    return UDR1;                    // retorna byte recebido
}

// programa principal
int main(void)
{
char lcd_buffer[20];
char com_serial;

	IO_init(); // inicia pinos de IO da placa.
	USART_init(); //inicia USART 
	lcd_init(LCD_DISP_ON); //inicia o LCD
	lcd_clrscr(); //Limpa tela do LCD
	sprintf(lcd_buffer,"Aperte ACK/BUSY");
	lcd_puts(lcd_buffer);

	while(1){

		if(Ch_busy_lig){
			USART_Send('A');
			while(Ch_busy_lig);
		}

		if(Ch_ack_lig)USART_Send('B');

		if(tem_caracter){
			com_serial=USART_Get();
			lcd_gotoxy(0,1);
			lcd_putc(com_serial);

			if(com_serial=='A')Liga_Strobe();
			if(com_serial=='B')Desliga_Strobe();
		}
	}
}
