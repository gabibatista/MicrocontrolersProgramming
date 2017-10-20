#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>

// inclui no projeto os arquivos .c e .h
#include "funcoes.h"
#include "lab_uino.h"
#include "lcd_usb.h"

int main(void)
{
  IO_init(); // inicia o IO
  char* ldc_buffer[17];

  int ligar = 0;
  int minutos = 0;
  int segundos = 0;
  Timer0_init();
  sei();
  tempo[0] = 0;

  lcd_init(LCD_DISP_ON); // inicializa o display

  while(1){
  	if (tempo[0] >= 1024){
		tempo[0] = 0;
		if (ligar == 0)
			ligar = 1;
		else
			ligar = 0;
		
		if (ligar)
			Liga_D0();
		else
			Desliga_D0();
	  segundos++;
	  if (segundos = 60){
	  	segundos = 0;
		minutos++;
	  }

	  if (minutos = 60)
	  	minutos = 0;

      sprintf(ldc_buffer, "%i:%i", minutos, segundos);

	  lcd_gotoxy(0,0); // define a posição em que será printado

	  lcd_puts(ldc_buffer);
	}
  }
}

