#!/bin/bash
make iso
qemu-system-i386 -cdrom iridium.iso
