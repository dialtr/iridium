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

  // We'll fill the screen with the medium shaded block element character
  // from Code Page 737, using a foreground color of light grey and a
  // background color of black.
  const unsigned char MEDIUM_SHADED_BLOCK_CHAR = 177;

  // Fill the entire screen with the shaded character.
  vga_fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, MEDIUM_SHADED_BLOCK_CHAR,
                VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}
