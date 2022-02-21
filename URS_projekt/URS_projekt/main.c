#define F_CPU 7372800UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <spi.h>
#include <mfrc522.h>
#include <stdio.h>

void writeUsart(char *str){
	//unsigned char data[] = str;
	int i = 0;
	while(str[i] != 0)
	{
		while (!( UCSRA & (1<<UDRE)));
		
		UDR = str[i];
		i++;
	}
	_delay_ms(10);
}

void usart_init(){
	//	UBRR = 4800
	//	ODD PARITY
	//  6 BIT TRANSFER
	//  2 STOP BITS
	
	unsigned int ubrr = 95;
	
	UBRRH = (ubrr>>8);
	UBRRL = (ubrr);
	
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UPM0) | (1 << UPM1) | (1 << USBS);
	UCSRB = (1 << TXEN) | (1 << RXEN);
}


int main()
{
	char stri[8];
	uint8_t byte = 0;
	uint8_t str[MAX_LEN];
	_delay_ms(50);
	DDRA = 0xff;
	usart_init();	
	//writeUsart("1235");
		
	spi_init();
	//PORTA = ~SPCR;
	_delay_ms(100);
	
	mfrc522_init();
	
	byte = mfrc522_read(VersionReg);
	PORTA = byte;
	if(byte == 0x92)
	{
		writeUsart("522:2");
	}else if(byte == 0x91 || byte==0x90)
	{
		writeUsart("522:1");
	}else
	{
		writeUsart("0101\n");
	}
	sprintf(stri, "%d", byte);
	writeUsart(stri);
	
	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);
	
	_delay_ms(1500);
	
	while(1){
		byte = mfrc522_request(PICC_REQALL,str);
		sprintf(stri, "%d\n", byte);
		writeUsart(stri);
		_delay_ms(1000);
	}
	
}