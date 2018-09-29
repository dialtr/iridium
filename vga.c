/*
 * vga.c
 *
 * Copyright (C) 2018 The iridium authors.
 * All rights reserved.
 */
#include "vga.h"


// The base address of the VGA screen buffer.
static uint16_t* vga_screen_buffer = 0;


// Make an color attribute entry given foreground, background colors.
inline uint8_t vga_make_color_entry(enum vga_color fg, enum vga_color bg) {
	return (fg | (bg << 4));
}


// Make a pattern entry given a character and a color.
inline uint16_t vga_make_char_pattern(unsigned char ch, uint8_t color) {
  return (((uint16_t)ch) | (((uint16_t)(color)) << 8));
}


// Initialize the VGA driver and clear the screen.
vga_status_t vga_init() {
	vga_screen_buffer = (uint16_t*) 0xB8000;
	return vga_clear();
}


// Clear the screen buffer.
vga_status_t vga_clear() {
  // We don't check to see if the library is initialized; we delegate that
	// check to vga_fill_rect(), which will perform it for us.

  // Fill the buffer with spaces. Foreground color is light grey and
  // backgound color is black, although the foreground color could
  // be anything since we're filling the buffer with spaces.

  return vga_fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, ' ',
      VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}


// Fill a rectangle in the buffer with the specified code point, attributes.
vga_status_t vga_fill_rect(size_t x,
		                       size_t y,
									         size_t width,
									         size_t height,
									         unsigned char cp,
									         enum vga_color fgcolor,
									         enum vga_color bgcolor) {

	// Ensure the library is initialized.
	if (vga_screen_buffer == 0) {
		return VGA_NOT_INITIALIZED;
	}

	// Calculate extents of the rectangle.
	const size_t x_ext = (x + width);
	const size_t y_ext = (y + height);

	// Perform range check on the arguments.
	if ((x >= VGA_WIDTH) ||
			(y >= VGA_HEIGHT) ||
		  (x_ext > VGA_WIDTH) ||
			(y_ext > VGA_HEIGHT)) {
	  return VGA_INVALID_DIMENSION;
	}

	// Make the character pattern, to be repeated in the rectangle.
	const uint16_t pattern = vga_make_char_pattern(cp,
			vga_make_color_entry(fgcolor, bgcolor));

	// Draw the character pattern in all locations in the rectangle.
	for (size_t j = y; j < y_ext; ++j) {
	  for (size_t i = x; i < x_ext; ++i) {
		  const size_t offset = (j * VGA_WIDTH) + i;
			vga_screen_buffer[offset] = pattern;
		}
	}
  
  return VGA_SUCCESS;
}

