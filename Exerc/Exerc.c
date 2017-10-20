#include <avr/io.h>
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>

// inclui no projeto os arquivos .c e .h
#include "funcoes.h"
#include "lab_uino.h"
#include "lcd_usb.h"

void evento_direita(){
	Liga_Strobe();
	_delay_ms(200); // aguarda 1s
    Desliga_Strobe();

	Liga_Feed();
	_delay_ms(200); // aguarda 1s
	Desliga_Feed();

	Liga_Sel_in();
	_delay_ms(200);
	Desliga_Sel_in();	

	Liga_Init();
	_delay_ms(200);
	Desliga_Init();

	Liga_D0();
	_delay_ms(200); // aguarda 1s
	Desliga_D0();

	Liga_D1();
	_delay_ms(200); // aguarda 1s
	Desliga_D1();

	Liga_D2();
	_delay_ms(200); // aguarda 1s
	Desliga_D2();

	Liga_D3();
	_delay_ms(200); // aguarda 1s
	Desliga_D3();

}

void evento_esquerda(){

	Liga_D3();
	_delay_ms(200); // aguarda 1s
	Desliga_D3();

	Liga_D2();
	_delay_ms(200); // aguarda 1s
	Desliga_D2();

	Liga_D1();
	_delay_ms(200); // aguarda 1s
	Desliga_D1();

	Liga_D0();
	_delay_ms(200); // aguarda 1s
	Desliga_D0();

	Liga_Init();
	_delay_ms(200);
	Desliga_Init();

	Liga_Sel_in();
	_delay_ms(200);
	Desliga_Sel_in();

	Liga_Feed();
	_delay_ms(200); // aguarda 1s
	Desliga_Feed();

	Liga_Strobe();
	_delay_ms(200); // aguarda 1s
    Desliga_Strobe();

}

void evento_paraMeio(){
  Liga_D3();
  Liga_Strobe();
  _delay_ms(200); // aguarda 1s
  Desliga_Strobe();
  Desliga_D3();

  Liga_D2();
  Liga_Feed();
  _delay_ms(200); // aguarda 1s
  Desliga_Feed();
  Desliga_D2();

  Liga_D1();
  Liga_Sel_in();
  _delay_ms(200);
  Desliga_Sel_in();
  Desliga_D1();

  Liga_D0();
  Liga_Init();
  _delay_ms(200);
  Desliga_Init();
  Desliga_D0();
}


int main(void)
{
  IO_init(); // inicia o IO

  char* ldc_buffer[16];
  
  char* opcoesMenu[4] = {"Escolher Led", "Intensidade", "Efeito", "Apagar tudo"}; // instancia o vetor de strings com as opções do menu

  char* escolherLed[4] = {"Led 4", "Led 5", "Strobe", "Todas"}; // instancia o vetor de strings com as opções do submenu de escolher Led

  int intensidade = 1, menu = 0, submenu = 0, submenuE = 0; // instancia as variáveis de intensidade, de controle de índice do menu e do submenu

  int led4 = 0, led5 = 0, strobe = 0, todas = 0;

  char* efeito[3] = {"Direita", "Esquerda", "Para o meio"}; // instancia o vetor de strings com as opções do submenu de efeito

  lcd_init(LCD_DISP_ON); // inicializa o display
  lcd_clrscr(); // limpa a tela
  sprintf(ldc_buffer, opcoesMenu[0]); // printa na tela a primeira opção
  lcd_gotoxy(0,0); // define a posição em que será printado
  lcd_puts(ldc_buffer); 
  

  while (1){ // while infinito
  	//for (int i = 0; i < 256; i++){ //altera i de 0 a 255
	  //_delay_ms(200);  // aguarda 20 ms
	  //Set_PWM_T1C(i); // muda a intensidade do PWDT1A de acordo com i
	//}

    if (Ch_sel_out_lig){ // botão up
	   lcd_clrscr();
       if (menu == 0){ // se a primeira opção está sendo exibida
	     menu = 3; // vai para a última opção
	   } 
	   else if (menu != 0){ // caso não seja a primeira opção
	     menu = menu - 1; // decrementa o índice de menu
	   }
       sprintf(ldc_buffer, opcoesMenu[menu]); //
       lcd_gotoxy(0,0);
       lcd_puts(ldc_buffer);
	}

	if (Ch_paper_out_lig){ // botão down
	   lcd_clrscr();
	   
	   if (menu == 3){ // se a última opção está sendo exibida
	     menu = 0; // vai para a primeira opção
		 sprintf(ldc_buffer, opcoesMenu[menu]);
	   }
	    
	   else if (menu != 3){
	     menu = menu + 1;
		 sprintf(ldc_buffer, opcoesMenu[menu]);
	   }

       lcd_gotoxy(0,0);
       lcd_puts(ldc_buffer);
	}

	if (Ch_ack_lig){ //botão enter
	   lcd_clrscr();

       if (menu == 0){ // se a primeira opção foi a escolhida, foi escolhido o Escolher led
	      sprintf(ldc_buffer, escolherLed[submenu]);
          lcd_gotoxy(0,0);
          lcd_puts(ldc_buffer);

		  while (1){
		      if (Ch_sel_out_lig){ // botão up
			    lcd_clrscr();

		        if (submenu == 0){ // se a primeira opção está sendo exibida
			      submenu = 3; // vai para a última opção
			    } 

			    else if (submenu != 0){
			      submenu = submenu - 1;
			    }

		        sprintf(ldc_buffer, escolherLed[submenu]);
		        lcd_gotoxy(0,0);
		        lcd_puts(ldc_buffer);
			 }

			 if (Ch_paper_out_lig){ // botão down
			    lcd_clrscr();
    
		 	    if (submenu == 3){ // se a última opção está sendo exibida
			      submenu = 0; // vai para a primeira opção
			    }
   
			    else if (submenu != 3){
			      submenu = submenu + 1;
			    }

				sprintf(ldc_buffer, escolherLed[submenu]);
		        lcd_gotoxy(0,0);
		        lcd_puts(ldc_buffer);
			 }
        
			 if (Ch_ack_lig){ //botão enter
      		   if (submenu == 0){ // se a opção escolhida foi 0 -> Led 4
				  Liga_D4();
				  Desliga_D5();
				  Desliga_Strobe();
			   }
			   else if (submenu == 1){ // se a opção escolhida foi 1 -> Led 5
			      Liga_D5();
				  Desliga_D4();
				  Desliga_Strobe();
			   }
			   else if (submenu == 2){ // se a opção escolhida foi 2 -> Strobe
			      Liga_Strobe();
				  Desliga_D4();
				  Desliga_D5();
			   }
			   else if (submenu == 3){ // se a opção escolhida foi 3 -> Todas
			      Liga_D4();
				  Liga_D5();
				  Liga_Strobe();
			   }
			 }

			 if (Ch_error_lig){ //botão esc
				sprintf(ldc_buffer, escolherLed[submenu]);
                lcd_gotoxy(0,0);
                lcd_puts(ldc_buffer);
				break;
	         }
	     }
		 }
		 
		 else if (menu == 1){ // se a opção escolhida no menu == 1 -> escolheu intensidade
		 	sprintf(ldc_buffer, "Intensidade: %d", intensidade);
            lcd_gotoxy(0,0);
            lcd_puts(ldc_buffer);

			while (1){
			  if (Ch_prog_lig){ // botão left
			    if (intensidade > 0){
			      intensidade = intensidade - 1;
 				  Set_PWM_T1C(intensidade);

				  _delay_ms(50); // aguarda 1s

				  lcd_clrscr();

				  sprintf(ldc_buffer, "Intensidade: %d", intensidade);
                  lcd_gotoxy(0,0);
                  lcd_puts(ldc_buffer);
				}
			  }
			  else if (Ch_busy_lig){ //botão right
				if (intensidade < 255){
				  intensidade = intensidade + 1;

				  Set_PWM_T1C(intensidade);

				  _delay_ms(50); // aguarda 1s

			      lcd_clrscr();

				  sprintf(ldc_buffer, "Intensidade: %d", intensidade);
                  lcd_gotoxy(0,0);
                  lcd_puts(ldc_buffer);
				}
			  }
			  else if (Ch_error_lig){ //botão esc
				sprintf(ldc_buffer, escolherLed[submenu]);
                lcd_gotoxy(0,0);
                lcd_puts(ldc_buffer);
				break;
	          }
			}
		 }
		 else if (menu == 2){ // se a opção escolhida no menu == 2 -> escolheu efeito
		 	sprintf(ldc_buffer, efeito[submenuE]);
            lcd_gotoxy(0,0);
            lcd_puts(ldc_buffer);

		    while (1){
		      if (Ch_sel_out_lig){ // botão up
			    lcd_clrscr();

		        if (submenuE == 0){ // se a primeira opção está sendo exibida
			      submenuE = 2; // vai para a última opção
			    } 

			    else if (submenuE != 0){
			      submenuE = submenuE - 1;
			    }

		        sprintf(ldc_buffer, efeito[submenuE]);
		        lcd_gotoxy(0,0);
		        lcd_puts(ldc_buffer);
			 }

			 if (Ch_paper_out_lig){ // botão down
			    lcd_clrscr();
    
		 	    if (submenuE == 2){ // se a última opção está sendo exibida
			      submenuE = 0; // vai para a primeira opção
			    }
   
			    else if (submenuE != 2){
			      submenuE = submenuE + 1;
			    }

				sprintf(ldc_buffer, efeito[submenuE]);
		        lcd_gotoxy(0,0);
		        lcd_puts(ldc_buffer);
			 }
        
			 if (Ch_ack_lig){ //botão enter
      		   if (submenuE == 0){ // se escolhida a opção 0 -> Efeito Direita (para a esquerda)
				  evento_direita();
			   }
			   else if (submenuE == 1){ // se escolhida a opção 1 -> Efeito esquerda (para a Direita)
			      evento_esquerda();
			   }
			   else if (submenuE == 2){ // se escolhida a opção 2 -> Efeito para o meio
			      evento_paraMeio();
			   }
			 }

			 if (Ch_error_lig){ //botão esc
				sprintf(ldc_buffer, escolherLed[submenu]);
                lcd_gotoxy(0,0);
                lcd_puts(ldc_buffer);
				break;
	         }

		   _delay_ms(1000);

	     }}
		 else if (menu == 3){ // se a opção escolhida no menu == 3 -> escolheu apagar todas
			Desliga_D4();
			Desliga_D5();
			Desliga_Strobe();
		 	// apagar todas as leds acesas.
		 }

	   
	}
	  
    _delay_ms(1000);
	
  }



  return 0;
}

