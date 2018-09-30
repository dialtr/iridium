/*
 * kernel_main.c
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

#if defined(__linux__)
#error "Building the kernel requires an appropriate i686 cross compiler."
#endif

#if !defined(__i386)
#error "Building the kernel requires an x86 elf compiler."
#endif

void kernel_main(void) {
  // Initialize the VGA driver.
  vga_init();

  const uint8_t SPACE = ' ';

  // Fill the entire screen with the shaded character.
  vga_fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, SPACE, VGA_COLOR_WHITE,
                VGA_COLOR_BLUE);

  const uint8_t message[] = "Hello, Iridium!";

  vga_draw_text(0, 24, message, sizeof(message) / sizeof(uint8_t),
                VGA_COLOR_WHITE, VGA_COLOR_BLUE);
}
