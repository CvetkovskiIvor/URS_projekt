#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "spi.h"
#include "mfrc522.h"
#include <stdio.h>

void usart_init(){
	//	UBRR = 4800
	//	ODD PARITY
	//  7 BIT TRANSFER
	//  2 STOP BITS
	
	unsigned int ubrr = 95;
	
	UBRRH = (ubrr>>8);
	UBRRL = (ubrr);
	
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UPM0) | (1 << UPM1) | (1 << USBS);
	UCSRB = (1 << TXEN) | (1 << RXEN);
}

void detectReaderVersion() {
	//check version of the reader
	uint8_t byte = mfrc522_read(VersionReg);
	
	if (byte == 0x92) {
		usart_puts("Reader detected ");
		usart_puts("MIFARE RC522 v2\n");

		} else if (byte == 0x91 || byte==0x90) {
		usart_puts("Reader detected ");
		usart_puts("MIFARE RC522v1\n");
		} else {
		usart_puts("No reader found\n");
		PORTA = byte;
	}
}

int main()
{
	uint8_t str[16];
	// used for storing status after communication with the reader
	uint8_t status;
	
	_delay_ms(50);
	usart_init();
	
	spi_init();
	_delay_ms(10);
	
	mfrc522_init();
	_delay_ms(10);
	
	detectReaderVersion();
	_delay_ms(1000);
	
	while(1){
		// request information about any tag in range of the antenna
		status = mfrc522_request(PICC_REQALL,str);
		
		if(status == CARD_FOUND) {
			// if card is found, try to fetch card id number
			status = mfrc522_get_card_serial(str);
			
			if(status == CARD_FOUND) {
				// send id number (as hex characters) through USART interface
				for(uint8_t i = 0; i < 5; ++i) {
					usart_hex(str[i]);
				}
			}
			else {
				usart_puts("Error reading serial!\n");
			}
			_delay_ms(1000);
		}
		
		// Test for a tag every 1000ms
		_delay_ms(1000);
	}
	
}