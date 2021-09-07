#define NORMAL_MODE 0
#define MOVE_TO_MODE 1

#define POWER_TIME_MS 750

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

typedef struct LED LED;
struct LED
{
	uint8_t mode;
	uint8_t setPointR, setPointG, setPointB;
	float R, G, B;
	float alphs[3];
};

void led_ini(LED *led);
void led_tick(LED *led);
void led_update(LED *led);
void led_setRGB(LED *led, uint8_t R, uint8_t G, uint8_t B);
void led_setRGB_HEX(LED *led, uint32_t hex);
void led_moveTo(LED *led, uint8_t setPointR, uint8_t setPointG,
				uint8_t setPointB, uint32_t perTimeMs);
void led_moveTo_HEX(LED *led, uint32_t hex, uint32_t perTimeMs);
void led_power(LED *led);