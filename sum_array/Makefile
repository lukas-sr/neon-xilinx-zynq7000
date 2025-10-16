CC=arm-none-eabi-gcc
CFLAGS=-O3 -mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -c -Wall -I./include
LDFLAGS=-mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -Wl,-build-id=none -specs=Xilinx.spec -Wl,-T -Wl,lscript.ld -Llib
LIBS=-Wl,--start-group,-lxil,-lgcc,-lc,--end-group

all: main.elf

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c

neon.o: neon.c
	$(CC) $(CFLAGS) -o neon.o neon.c

platform.o: platform.c
	$(CC) $(CFLAGS) -o platform.o platform.c

main.elf: main.o neon.o platform.o
	$(CC) $(LDFLAGS) -o main.elf main.o neon.o platform.o $(LIBS)

clean:
	rm *.o main.elf
