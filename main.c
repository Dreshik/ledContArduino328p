#define F_CPU 16000000UL
#include <avr/io.h>
#include "components/UART/Uart.h"
#include "components/LED/LED.h"

UART uart;
LED led;

int main()
{
	uart_ini(&uart, UART_SPEED_9600);
	led_ini(&led);

	sei();

	while (1)
	{

	}

	return 1;
}

ISR (TIMER0_OVF_vect)
{
	led_tick(&led);
}
