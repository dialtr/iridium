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

iridium.iso: iridium.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp iridium.bin isodir/boot/iridium.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o iridium.iso isodir

.PHONY:
iso: iridium.iso

iridium.bin: boot.o kernel_main.o
	$(CC) -T linker.ld -o iridium.bin -ffreestanding -O2 -nostdlib boot.o \
		kernel_main.o -lgcc
	grub-file --is-x86-multiboot iridium.bin

boot.o: boot.s
	$(AS) $^ -o boot.o

kernel_main: kernel_main.c
	$(CC) $(CFLAGS) -c $^

.PHONY:
clean:
	-rm -f *.o *.bin
