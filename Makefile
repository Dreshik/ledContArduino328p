MCU = atmega328p
СС = avr-gcc
uart_dir = components/UART

UART: ${uart_dir}/Uart.c
	${СС} -Wall -mmcu=${MCU} -c -o ${uart_dir}/Uart.o ${uart_dir}/Uart.c

main: main.c
	${СС} -Wall -mmcu=${MCU} -o main.o ${uart_dir}/Uart.o main.c

all: UART main
	avr-objcopy -j .text -j .data -O ihex main.o image/firmware.hex

clean:
	rm main.o
	rm ${uart_dir}/Uart.o