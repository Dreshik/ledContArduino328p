#include "Uart.h"

void uart_ini(UART *uart, uint16_t speed)
{
	uart->speed = speed;
	UBRR0H = speed>>8;
	UBRR0L = speed;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

uint16_t uart_print_str(const char *str)
{
	uint16_t i = 0;
	for (; i < strlen(str); i++)
		uart_print_char(str[i]);
	return i;
}

void uart_print_char(const char ch)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
}