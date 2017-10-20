#include <avr/io.h>
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
  int valor, qntdX, aux;

  lcd_init(LCD_DISP_ON); // inicializa o display

  while (1){
	  valor = Read_ADC(1);
	  
	  aux = valor;

	  for (qntdX = 0; aux >= 64; qntdX++){
	  	aux = aux - 64;
	  }

	  sprintf(ldc_buffer, " ");
	
      for (int i = 0; i <= qntdX; i++)
	  	ldc_buffer[i] = '*';

	  lcd_gotoxy(0,0); // define a posição em que será printado

	  lcd_puts(ldc_buffer);
  }

  return 0;
}

