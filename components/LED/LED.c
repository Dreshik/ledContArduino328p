#include "LED.h"

void led_ini(LED *led)
{
	led->R = 0;
	led->G = 0;
	led->B = 0;
	led->mode = NORMAL_MODE;

	DDRD |= (1<<6); // B
	EIMSK |= (1<<INT0); 
	EICRA |= (1<<ISC00) | (1<<ISC01);

	TCCR0A |= (1<<WGM00) | (1<<WGM01); // FAST PWM 8bit
	TCCR0A |= (1<<COM0A1);
	TCCR0B |= (1<<CS00) | (1<<CS01); // pre 64
	TCCR0B &= ~(1<<CS02);
	TIMSK0 |= (1<<TOIE0); 

	DDRB |= (1<<1) | (1<<2); // G, R
	TCCR1B |= (1<<CS10) | (1<<CS11);// pre 64
	TCCR1A |= (1<<WGM10); // fast PWM 8bit
	TCCR1B |= (1<<WGM12);
	TCCR1A |= (1<<COM1A1);
	TCCR1A |= (1<<COM1B1);

	led_update(led);
}

void led_tick(LED *led)
{
	switch (led->mode)
	{
		case NORMAL_MODE:
		{
			break;
		}
		case MOVE_TO_MODE:
		{
			led->R+= led->alphs[0];
			if (abs(led->R - led->setPointR) < 1)
			{
				led->R = led->setPointR;
				led->alphs[0] = 0;
			}

			led->G+= led->alphs[1];
			if (abs(led->G - led->setPointG) < 1)
			{
				led->G = led->setPointG;
				led->alphs[1] = 0;
			}

			led->B+= led->alphs[2];
			if (abs(led->B - led->setPointB) < 1)
			{
				led->B = led->setPointB;
				led->alphs[2] = 0;
			}

			if ((led->alphs[0] == 0) && (led->alphs[1] == 0) &&
				(led->alphs[2] == 0))
			{
				led->mode = NORMAL_MODE;
			}
			break;
		}
	}
	led_update(led);
}

void led_update(LED *led)
{
	//OCR1B = R; 10 PIN arduino. PB2
	//OCR1A = G; 9 PIN arduino. PB1
	//OCR0A = B; 7 or 6 PIN arduino. PD6
	if (led->R != OCR1B)
	{
		OCR1B = led->R;
		if (led->R > 0)
			DDRB |= (1<<2);
		else
			DDRB &= ~(1<<2);
	}
	if (led->G != OCR1A)
	{
		OCR1A = led->G;
		if (led->G > 0)
			DDRB |= (1<<1);
		else
			DDRB &= ~(1<<1);
	}
	if (led->B != OCR0A)
	{
		OCR0A = led->B;
		if (led->B > 0)
			DDRD |= (1<<6);
		else
			DDRD &= ~(1<<6);
	}
}

void led_setRGB(LED *led, uint8_t R, uint8_t G, uint8_t B)
{
	led->R = R;
	led->G = G;
	led->B = B;
	led_update(led);
}

void led_setRGB_HEX(LED *led, uint32_t hex)
{
	uint8_t newR = hex>>16;
	uint8_t newG = (hex>>8)&255;
	uint8_t newB = hex&255;
	led_setRGB(led ,newR, newG, newB);
}

void led_moveTo(LED *led, uint8_t setPointR, uint8_t setPointG,
				uint8_t setPointB, uint32_t perTimeMs)
{
	led->setPointR = (float)setPointR;
	led->setPointG = (float)setPointG;
	led->setPointB = (float)setPointB;

	led->alphs[0] = (float)(led->setPointR - led->R)/perTimeMs;
	led->alphs[1] = (float)(led->setPointG - led->G)/perTimeMs;
	led->alphs[2] = (float)(led->setPointB - led->B)/perTimeMs;
	led->mode = MOVE_TO_MODE;
}

void led_moveTo_HEX(LED *led, uint32_t hex, uint32_t perTimeMs)
{
	uint8_t newR = hex>>16;
	uint8_t newG = (hex>>8)&255;
	uint8_t newB = hex&255;
	led_moveTo(led, newR, newG, newB, perTimeMs);
}

void led_power(LED *led)
{
	if (led->R != 0 || led->G != 0 || led->B != 0)
		led_moveTo_HEX(led, 0, POWER_TIME_MS);
	else
		led_moveTo_HEX(led, 0xFFFFFF, POWER_TIME_MS);
}