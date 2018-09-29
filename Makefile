export PATH := $(HOME)/opt/cross/bin:$(PATH)

AR=i686-elf-ar
AS=i686-elf-as
CC=i686-elf-gcc
LD=i686-elf-ld

.PHONY:
all: iridium

.PHONY:
iridium: boot.o

boot.o: boot.s
	$(AS) $^ -o boot.o

.PHONY:
clean:
	-rm -f boot.o
