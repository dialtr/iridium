/*
 * kernel_main.c
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "splash.h"
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

  // Display the Iridum startup/splash screen.
  display_splash_screen();
}
