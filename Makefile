export PATH := $(HOME)/opt/cross/bin:$(PATH)

AR=i686-elf-ar
AS=i686-elf-as
CC=i686-elf-gcc
LD=i686-elf-ld

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

.PHONY:
all: iridium

.PHONY:
iridium: iridium.bin

iridium.bin: boot.o kernel_main.o
	$(CC) -T linker.ld -o iridium.bin -ffreestanding -O2 -nostdlib boot.o \
		kernel_main.o -lgcc

boot.o: boot.s
	$(AS) $^ -o boot.o

kernel_main: kernel_main.c
	$(CC) $(CFLAGS) -c $^

.PHONY:
clean:
	-rm -f *.o *.bin
