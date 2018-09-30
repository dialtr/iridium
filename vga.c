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
inline uint16_t vga_make_char_pattern(uint8_t ch, uint8_t color) {
  return (((uint16_t)ch) | (((uint16_t)(color)) << 8));
}

// Initialize the VGA driver and clear the screen.
vga_status_t vga_init() {
  vga_screen_buffer = (uint16_t*)0xB8000;
  return vga_clear();
}

// Clear the screen buffer.
vga_status_t vga_clear() {
  // We don't check to see if the library is initialized; we delegate that
  // check to vga_fill_rect(), which will perform it for us.

  // Fill the buffer with spaces. Foreground color is light grey and
  // backgound color is black, although the foreground color could
  // be anything since we're filling the buffer with spaces.
  return vga_fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, ' ', VGA_COLOR_LIGHT_GREY,
                       VGA_COLOR_BLACK);
}

// Draw a single character.
vga_status_t vga_draw_char(size_t x, size_t y, uint8_t cp,
                           enum vga_color fgcolor, enum vga_color bgcolor) {
  // Ensure the library is initialized.
  if (vga_screen_buffer == 0) {
    return VGA_NOT_INITIALIZED;
  }

  // Perform range check on the position.
  if ((x >= VGA_WIDTH) || (y >= VGA_HEIGHT)) {
    return VGA_INVALID_DIMENSION;
  }

  // Make the character pattern, to be repeated in the rectangle.
  const uint16_t pattern =
      vga_make_char_pattern(cp, vga_make_color_entry(fgcolor, bgcolor));

  // Calculate
  const size_t offset = (y * VGA_WIDTH) + x;

  // Write the character pattern to the screen buffer.
  vga_screen_buffer[offset] = pattern;

  return VGA_SUCCESS;
}

// Draw a text string.
vga_status_t vga_draw_text(size_t x, size_t y, const uint8_t* str, size_t len,
                           enum vga_color fgcolor, enum vga_color bgcolor) {
  // Ensure the library is initialized.
  if (vga_screen_buffer == 0) {
    return VGA_NOT_INITIALIZED;
  }

  // Perform range change on the position.
  if ((x >= VGA_WIDTH) || (y >= VGA_HEIGHT)) {
    return VGA_INVALID_DIMENSION;
  }

  // Ensure that the buffer is "valid" (not NULL).
  if (str == 0) {
    return VGA_INVALID_BUFFER;
  }

  // Calculate the total size of the screen buffer.
  const size_t buffer_size = VGA_WIDTH * VGA_HEIGHT;

  // Calculate the starting position in the buffer where we will begin writing
  // data. We know that this is valid because we performed a range check on
  // the arguments.
  const size_t start = (y * VGA_WIDTH) + x;

  // Calculate the maximum number of characters that we could conceivably
  // draw given the specified starting position and buffer_size;
  const size_t max_len = (buffer_size - start);

  // Potentially truncate the length of what we will draw. We do not want,
  // under any circumstances, to write past the end of the VGA buffer, as
  // that could lead to undefined behavior.
  len = (len > max_len) ? max_len : len;

  // Make the byte that contains color / attributes. It is reused.
  const uint8_t color_entry = vga_make_color_entry(fgcolor, bgcolor);

  // Write all the characters in the string.
  for (size_t i = 0; i < len; ++i) {
    // Make the pattern...
    const uint16_t pattern = vga_make_char_pattern(*(str + i), color_entry);

    // ...And write it to the buffer.
    vga_screen_buffer[start + i] = pattern;
  }

  return VGA_SUCCESS;
}

// Fill a rectangle in the buffer with the specified code point, attributes.
vga_status_t vga_fill_rect(size_t x, size_t y, size_t width, size_t height,
                           unsigned char cp, enum vga_color fgcolor,
                           enum vga_color bgcolor) {
  // Ensure the library is initialized.
  if (vga_screen_buffer == 0) {
    return VGA_NOT_INITIALIZED;
  }

  // Calculate extents of the rectangle.
  const size_t x_ext = (x + width);
  const size_t y_ext = (y + height);

  // Perform range check on the arguments.
  if ((x >= VGA_WIDTH) || (y >= VGA_HEIGHT) || (x_ext > VGA_WIDTH) ||
      (y_ext > VGA_HEIGHT)) {
    return VGA_INVALID_DIMENSION;
  }

  // Make the character pattern, to be repeated in the rectangle.
  const uint16_t pattern =
      vga_make_char_pattern(cp, vga_make_color_entry(fgcolor, bgcolor));

  // Draw the character pattern in all locations in the rectangle.
  for (size_t j = y; j < y_ext; ++j) {
    for (size_t i = x; i < x_ext; ++i) {
      // Calculate the offset into the VGA buffer for [i, j]
      const size_t offset = (j * VGA_WIDTH) + i;
      vga_screen_buffer[offset] = pattern;
    }
  }

  return VGA_SUCCESS;
}
