#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "components/UART/Uart.h"

UART uart;

int main()
{
	uart_ini(&uart, UART_SPEED_9600);
	sei();
	while (1)
	{

	}
	return 1;
}