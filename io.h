/*
 * io.h
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */
#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdint.h>

// Write a single byte to the specified port.
static inline void io_write_byte(uint16_t port, uint8_t value) {
  asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Read a single byte to the specified port.
static inline uint8_t io_read_byte(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

// Perform a delay (used when we need a minor delay between IO's)
static inline void io_wait(void) {
  // Port 0x80 is used for 'checkpoints' during POST.
  // The Linux kernel seems to think it is free for use.
  asm volatile("outb %%al, $0x80" : : "a"(0));
}

#endif  // IO_H_INCLUDED
