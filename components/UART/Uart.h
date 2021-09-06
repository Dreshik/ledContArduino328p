#define UART_SPEED_9600   103
#define UART_SPEED_14400  68
#define UART_SPEED_38400  103
#define UART_SPEED_115200 3
#define UART_SPEED_250000 3
#define UART_SPEED_500000 1

#include <avr/io.h>
#include <string.h>

typedef struct UART UART;
struct UART
{
	uint16_t speed;
};

void uart_ini(UART *uart, uint16_t speed);
uint16_t uart_print_str(const char *srt);
void uart_print_char(const char ch);