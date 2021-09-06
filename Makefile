MCU = atmega328p
СС = avr-gcc

main: main.c
	${СС} -Wall -mmcu=${MCU} -o main.o main.c

all: main
	avr-objcopy -j .text -j .data -O ihex main.o image/firmware.hex

clean:
	rm main.o