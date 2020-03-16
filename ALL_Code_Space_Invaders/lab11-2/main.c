/*
 * lab11-2.c
 *
 * Created: 2/20/2020 11:36:55 AM
 * Author : ahuec
 */ 

#include <avr/io.h>
//#include "lcd_8bit_task.h"
#include "timer.h"
#include "keypad.h"
#include "io.h"

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

char A[8][8] = { { 'B', 'A', 'A', 'A', 'A', 'A', 'A', 'B' }, { 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' }, 
	{ 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' }, { 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' },
		{ 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' }, { 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' },
			{ 'E', 'E', 'E', 'G', 'E', 'E', 'E', 'E' }, { 'B', 'E', 'S', 'S', 'S', 'E', 'E', 'B' }  };

unsigned char i;
const unsigned char LongStr[78] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'P','A','C','E', ' ', 
									'I', 'N', 'V','A', 'D', 'E', 'R', 'S', ' ', 'B', 'y', ' ', 'D', '.', 'H', 'u', 'e', 'c', 'k', 'e', 'r', ' ', 'p', 'r', 'e',
							 's', 's ', ' ', 's', 't', 'a', 'r', 't', ' ', 't', 'o', ' ', 'p', 'l', 'a', 'y', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '  };
							
char DisStr [16];
							
int check = 16;
int j = 16;
enum STATES {Start, Stop, Display}state;
	int temp = 0;
void tick_LCD (){
	switch(state)
	{
		case Start:
			state = Display;
			break;
			
		case Display:
			if (~PINA == 0x01){
			LCD_ClearScreen();
			state = Stop;
			}
			else
			state = Display;
		
			
			for(i =1; i<=16; i++){
				DisStr [i] = LongStr[i -1 + check -16 ];
				LCD_Cursor(i);
				LCD_WriteData(DisStr[i]);
			
				
				if(check == 78)
				{
					check = 16;
			
				}
					
			}
				//j--;
				check++;
				
				if(j ==1) {j =16;}
		
			break;

		case Stop:
			state = Stop;
			LCD_DisplayString(1, "test");
				break;
			
		default:
		state = Start;
		break;
	}
}
	


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xFF; PORTC = 0X00;
	DDRD = 0XFF; PORTD = 0X00;
	int sound = 0;
	int trig = 0;
	int i = 0;
	int drop = 0;
	int move = 0;
	int dead = 0;
	unsigned char score [12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11'};
	unsigned char temp = 0;
	int past = 200;
	TimerSet(200);
	TimerOn();
	LCD_init();
	//PWM_on();
	
		unsigned short x = ADC;
		ADC_init();
		unsigned short left = 700;
		unsigned short right = 300;
		int game = 0;
    /* Replace with your application code */
	PORTB = 0x00;
	PORTA = (0xFF);
	PORTD = 0xFF;
    while (1) 
    {	
		unsigned char temp = PORTA;
		//	x = ADC;
			
		//set_PWM(0);
		
		//if(temp != 0x02)
//		set_PWM(0);
		
		temp = ~PINA & 0x07;
		
		
		
		if(temp == 0x02 || dead == 2){
			LCD_ClearScreen();
		LCD_DisplayString(1, "High Score: 100 Your Score: ");
		i = 0;
		LCD_Cursor(29);
		LCD_WriteData(score[i]);
		trig = 1;
		game = 1;
		
		if(dead == 2)
		{dead = 3;
		
		}
		
		
		PORTB = 0x81;
		PORTA = ~(0x00);
		PORTD = 0xA3;
		//PORTB = 0x01;
		}
			
			if(temp == 0x04 && trig == 1){
				//score = score + 1;
				if (i == 13) { i = 0;};
				i = i +1;
				LCD_Cursor(29);
				LCD_WriteData(score[i]);
			//	set_PWM(261.66);
			
		//	PORTA = temp | 0x08;
			
			//PORTB = 0x02;
			sound = sound + 1;
		
			}
			
		//	PORTA = temp;
			
				//if (sound == 0)
				//PORTB = 0x08;
				//if(sound == 2)
				//{PORTB = 0x00;
					//sound = 0;}
				
			
			if(temp == 0x06)
			{
				LCD_ClearScreen();
				LCD_DisplayString(1, "Goodbye, Thanks For Playing!");
				trig = 0;
				
			//	PORTB = 0x04;
			}
			
			switch(drop){
				
				case 1:
						{
							PORTB = 0x41;
							break;
						}
				case 2:
				{
					PORTB = 0x21;
					break;
				}
			   case 3:
			 {
				 PORTB = 0x31;
				 break;
			 }
			 	case 4:
			 	{
				 	PORTB = 0x09;
				 	break;
			 	}
			 	case 5:
			 	{
				 	PORTB = 0x05;
				 	break;
			 	}
			 	case 6:
			 	{
				 	PORTB = 0x03;
				 	break;
			 	}
				 	case 7:
				 	{
					 	PORTB = 0xFF;
						 PORTA = 0X00;
						 PORTC = 0x00;
						 
						 LCD_ClearScreen();
						 LCD_DisplayString(1, "You Lost!");
						 trig = 0;
						 drop = 0;
						 game = 1;
						 dead = 1;
					 	break;
				 	}
				 	case 0:
				 	{
					 	PORTB = 0x81;
					 	break;
				 	}
					 default: break;
			 
			 
			}
			
			
			
			
			//if(temp == 0x07)
			//PORTB = 0x03;
			
	if(trig == 0 && game == 0)
{
		tick_LCD();
		while(!TimerFlag);
		TimerFlag = 0; 
}
else if (trig ==1 && game == 1 && past == 2800 ||  dead == 3 && past == 2800 ){
	while(!TimerFlag);
	TimerFlag = 0;
		drop = drop + 1;
		past = 0;
		dead = 0;
		//x = ADC;
		//unsigned char y = ADC;
		
		if(x > left){
			
			if(move == -3)
			{
				move = -3;
			}
			else
			move = move - 1;
			
			
		}
		if(x < right){
			//	PORTA =
			if(move == 2)
			{
				move = 2;
			}
			else{
			move = move + 1;}
			
		}
		
		switch(move){
			
			case 1:
			{
				PORTA = ~(0x00);
				PORTD = 0x71;
				break;
			}
			case 2:
			{
				PORTA = ~(0x00);
				PORTD = ~(0x07);
				break;
			}
			case -1:
			{
				PORTA = ~(0x00);
				PORTD = ~(0xF8);
				break;
			}
			case -2:
			{
				PORTA = ~(0x10);
				PORTD = ~(0xF0);
			}
			case -3:
			{
				PORTA = ~(0x30);
				PORTD = ~(0x20);
				break;
			}
			case 0:
			{
				PORTA = ~(0x00);
				PORTD = (0xA3);
				break;
			}
			
			default :
			{
				//PORTB = 0x03;
				break;
			}
			
			
		}
		
		
	
}
else{while(!TimerFlag);
	TimerFlag = 0;
	past = past + 200;
		if (dead == 1 && past == 3000)
		{dead = 2;
		if (dead != 0)
		PORTB = 0xFF;
		PORTA = (0x00);
		PORTD = 0x00;
		}
	}
		
			}
			}
