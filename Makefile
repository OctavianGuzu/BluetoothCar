all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $@

main.elf: *.c *.h
	avr-g++ -mmcu=atmega324a -DF_CPU=16000000 -O3 -Wall -o $@ $^

clean:
	rm -rf main.elf main.hex

.PHONY: all clean