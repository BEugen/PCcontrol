#ifndef USART_H
 #define USART_H
 #define BAUD0 9600
 #define BAUD1 9600
 #define Fck 4000000L
 #define DEVIDED ((int)(Fck/(8UL*BAUD0)-1))
 #define init_usart() \
   UCSRA = 0x22; \
   UCSRB = 0x98; \
   UCSRC = 0x06; \
   UBRRH = DEVIDED >> 8; \
   UBRRL = DEVIDED

void  putch(unsigned char byte);
void  putchrs( const unsigned char *byte, unsigned int count);
#endif
