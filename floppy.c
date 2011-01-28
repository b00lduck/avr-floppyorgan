#include "floppy.h"
#include "tools.h"

void position_head() {
	int i;

	CBI(PORTA,2);

	while(PIND & 2) {
		step_dec();
		delayloop16(60000);
	}

	for(i=0;i<30;i++) {
		step_inc();
		delayloop16(40000);
	}

	SBI(PORTA,2);
}


void step_dec() {
	SBI(PORTA,3);
	SBI(PORTA,4);
	CBI(PORTA,4);
}

void step_inc() {
	CBI(PORTA,3);
	SBI(PORTA,4);
	CBI(PORTA,4);
}
