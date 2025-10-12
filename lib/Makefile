CC= arm-none-eabi-gcc 

FLAGS= -g -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0

all: main.o startup_code.o final.elf

final.elf: main.o startup_code.o
	$(CC) $(FLAGS) --specs=rdimon.specs -Wl,-Map=final.map -T linker.ld *.o -o final.elf 

startup_code.o: startup_code.c
	$(CC) -c $(FLAGS) startup_code.c -o startup_code.o

main.o: main.c 
	$(CC) -c $(FLAGS) main.c -o main.o

clean:
	rm -rf *.o *.elf *.map

load:
	../../xpack-openocd-0.12.0-6/bin/openocd.exe -f ../../xpack-openocd-0.12.0-6/openocd/scripts/board/stm32f4discovery.cfg
