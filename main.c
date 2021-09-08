#define F_CPU 16000000UL
#include <avr/io.h>
#include "components/UART/Uart.h"
#include "components/LED/LED.h"
#include "components/IR/IR.h"

UART uart;
LED led;
IR ir;

int main()
{
	uart_ini(&uart, UART_SPEED_9600);
	led_ini(&led);
	ir_ini(&ir);
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

ISR(TIMER2_OVF_vect)
{
	ir_stop_read(&ir);
}

ISR(INT0_vect) 
{
	if (!ir.reading)
	{
		ir_start_read(&ir);
		TCNT2 = 0;
	}
	else
	{
		uint8_t dt = TCNT2;
		TCNT2 = 0;
		if (dt >= 30 && dt <= 40)
		{
			ir.data <<= 1;
			ir.data |= 1;
		}
		else if (dt <= 20)
		{
			ir.data <<= 1;
		}
	}
}
