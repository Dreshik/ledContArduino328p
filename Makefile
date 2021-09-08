MCU = atmega328p
СС = avr-gcc
uart_dir = components/UART
led_dir = components/LED
ir_dir = components/IR

IR: ${ir_dir}/IR.c
	${СС} -Wall -mmcu=${MCU} -c -o ${ir_dir}/IR.o ${ir_dir}/IR.c

LED: ${led_dir}/LED.c
	${СС} -Wall -mmcu=${MCU} -c -o ${led_dir}/LED.o ${led_dir}/LED.c

UART: ${uart_dir}/Uart.c
	${СС} -Wall -mmcu=${MCU} -c -o ${uart_dir}/Uart.o ${uart_dir}/Uart.c

main: main.c
	${СС} -Wall -mmcu=${MCU} -o main.o ${uart_dir}/Uart.o ${led_dir}/LED.o \
	${ir_dir}/IR.o main.c

all: IR LED UART main
	avr-objcopy -j .text -j .data -O ihex main.o image/firmware.hex

clean:
	rm main.o
	rm ${uart_dir}/Uart.o
	rm ${led_dir}/LED.o