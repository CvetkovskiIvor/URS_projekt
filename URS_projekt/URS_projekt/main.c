#define F_CPU 7372800UL
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	int i = 0;
	unsigned int ubrr = 23;
	unsigned char data[] = "MMMM";
	
	UBRRH = (ubrr>>8); 
	UBRRL = (ubrr);    
	
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);       
	UCSRB |= (1 << TXEN); 
	
	while(1) {
		i = 0;
		while(data[i] != 0) 
		{
			while (!( UCSRA & (1<<UDRE))); 
			
			UDR = data[i];	
			i++;                             
		}
		
		while (!( UCSRA & (1<<UDRE)));   
		UDR = '\n';			
		while (!( UCSRA & (1<<UDRE))); 
		UDR = '\r';
		
		_delay_ms(1000);
	}
	
}