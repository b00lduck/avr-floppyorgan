#include "stdinc.h"
#include "tools.h"
#include "usart.h"
#include "floppy.h"


uint16_t freqtable[65] = {82,87,92,97,103,109,116,122,130,138,146,154,164,173,184,194,206,218,231,245,260,275,291,309,327,346,367,389,412,437,462,490,
519,550,583,617,654,693,734,778,824,873,925,980,1038,1100,1165,1235,1308,1386,1468,1556,1648,1746,1850,1960,2077,2200,2331,
2469,2616,2772,2937,3111,3296};



void note_on(unsigned char nn) {
	TCNT1 = 0;	
	OCR1A = 2 * 15625 / freqtable[nn];
	TIMSK |= (1<<OCIE1A);
	CBI(PORTA,2);
}

void note_off(unsigned char nn) {
	TIMSK &= ~(1<<OCIE1A);
	SBI(PORTA,2);
}


int main() {

	usart_init();
	
	DDRA = 0b00011111;
	PORTA = 0;


	DDRD = 0b00000000;
	PORTD = 0b00000010;

	position_head();



  	//TIMSK |= (1<<OCIE1A); // Interrupt Compare A enable
  	TCCR1B |= (1<<CS10 | 1<<CS12 | 1<<WGM12); // Prescaler 1024  	
  	//OCR1A = (16000000 / 1024) / 110;

	sei();
	

	while(1) {

		char aa = USART_RX();
		char bb = USART_RX();
		char cc;

		char cmd = aa >> 4;
//		char ch = aa & 0x0f;

		switch(cmd) {

			case 0xa:
				cc = USART_RX();
				break;

			case 0xb:
				cc = USART_RX();
				break;

			case 0xe:
				cc = USART_RX();
				break;
				
			case 0xd:
				break;

			case 0xc:
				break;

			case 9:
				cc = USART_RX();
				if (cc > 0) {
					note_on(bb);
				} else {
					note_off(bb);
				}
				break;

			case 8:
				cc = USART_RX();
				note_off(bb);
				break;

		}

	}

}


char state_x = 0;
unsigned char state_dir = 0;


ISR (TIMER1_COMPA_vect) {

	if (state_dir == 0) {
		
		step_inc();
		state_x++;

		if (state_x >= 1) {
			state_dir = 1;
		}
		
	} else {

		step_dec();
		state_x--;

		if (state_x <= 0) {
			state_dir = 0;
		}

	}


}
