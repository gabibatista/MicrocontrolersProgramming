#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>

#include "lcd_usb.h"

#define F_CPU	4000000UL

/*ADC Conversion Complete Interrupt Service Routine (ISR)*/
ISR(ADC_vect);
 
#define LCD_DATA_PORT	PORTB
#define LCD_DATA_DDR	DDRB
#define LCD_DATA_PIN	PINB
 
#define LCD_CNTRL_PORT	PORTC
#define LCD_CNTRL_DDR	DDRC
#define LCD_CNTRL_PIN	PINC
 
#define LCD_RS_PIN		5
#define LCD_RW_PIN		6
#define LCD_ENABLE_PIN	7
#define SET_HOUR		3
#define SET_MINUTE		4
 
int main(void)
{
	unsigned char i; 
 
    lcd_init(LCD_DISP_ON); // inicializa o display
	lcd_gotoxy(0,0);
	lcd_puts("Temperature is");
 
 
	LCD_CNTRL_PORT = (1<<SET_HOUR | 1<<SET_MINUTE);
 
//	DDRA = 0x00;			// Configure PortA as input
 
	ADCSRA = 0x8F;			// Enable the ADC and its interrupt feature
					// and set the ACD clock pre-scalar to clk/128
	ADMUX = 0xE0;			// Select internal 2.56V as Vref, left justify 
					// data registers and select ADC0 as input channel 
 
	sei();				// Enable Global Interrupts
	ADCSRA |= 1<<ADSC;		// Start Conversion
 
	while(1);
}
 
/*ADC Conversion Complete Interrupt Service Routine (ISR)*/
ISR(ADC_vect)
{	
	char tempC, tempF, display;
	float tempff;
 
	tempC = ADCH;			// Output ADCH to PortD
	tempff = (float)tempC;
	tempff = (tempff*9)/5 + 32;	
	tempF = tempff;
 
    lcd_gotoxy(2,4);	
	itoa(tempC/10,display,10);
	lcd_puts(display);
	itoa(tempC%10,display,10);
	lcd_puts(display);
	lcd_data(0xDF);
	lcd_puts("C   ");
	itoa(tempF/10,display,10);
	lcd_puts(display);
	itoa(tempF%10,display,10);
	lcd_puts(display);
	lcd_data(0xDF);
	lcd_puts("F");
	_delay_ms(500);
	ADCSRA |= 1<<ADSC;		// Start Conversion
}
