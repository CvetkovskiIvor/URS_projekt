#define F_CPU 7372800UL
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	//
	//	UBRR = 4800
	//	ODD PARITY
	//  7 BIT TRANSFER
	//  2 STOP BITS
	//
	int i = 0;
	unsigned int ubrr = 95;
	unsigned char data[] = "IDE GAS!!!!! ";
	
	UBRRH = (ubrr>>8);
	UBRRL = (ubrr);  
	
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UPM1) | (1 << UPM0) | (1 << USBS);       
	UCSRB |= (1 << TXEN); 
	
	while(1) {
		
		i = 0;
		while(data[i] != 0) 
		{
			while (!( UCSRA & (1<<UDRE))); 
			
			UDR = data[i];	
			i++;                             
		}
		
		//while (!( UCSRA & (1<<UDRE)));   
		//UDR = '\n';			
		//while (!( UCSRA & (1<<UDRE))); 
		//UDR = '\r';
		
		
		_delay_ms(1);
	}
	
}