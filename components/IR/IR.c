#include "IR.h"

void ir_ini(IR *ir)
{
	ir->data = 0;
	ir->reading = 0;
	ir->DRDY = 0;
	ir->index = 0; 
}

void ir_start_read(IR *ir)
{
	ir->data = 0;
	ir->reading = 1;
	ir->DRDY = 0;
	TIMSK2 = (1 << TOIE0);
	TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22);
}

void ir_stop_read(IR *ir)
{
	TIMSK2 &= ~(1 << TOIE0);
	TCCR2B &= ~((1<<CS20) | (1<<CS21) | (1<<CS22));
	ir->reading = 0;
	ir->DRDY = 1;
}
