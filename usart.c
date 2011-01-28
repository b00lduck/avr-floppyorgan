#include "stdinc.h"
#include "tools.h"
#include "usart.h"

void usart_init() {

	UBRRH = 0; 
	UBRRL = 31; // 31250 bit/s

	UCSRB = (1<<RXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}


char USART_RX(void) {
    while (!(UCSRA & (1<<RXC))) {	};
	return UDR;
}

/*
void USART_RXS(void) {
	unsigned char t = 0;
	char* b = buffer;
	unsigned char len = LINEBUFFER_LENGTH;
	do {
 		t = USART_RX();
		SBI(PORTC,0);
		if (len) {
			*b++ = t;
			len--;
		}
		CBI(PORTC,0);
	} while(t != 13);
	*b = 0; // ende
}
*/
