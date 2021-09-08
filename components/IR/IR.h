#include <avr/io.h>

typedef struct IR IR;
struct IR
{
	uint32_t data;
	uint8_t reading;
	uint8_t index; 
	volatile uint8_t DRDY;
};

void ir_ini(IR *ir);
void ir_start_read(IR *ir);
void ir_stop_read(IR *ir);

