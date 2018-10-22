/*
 * vga.h
 *
 * Copyright (C) 2018 The iridium authors.
 * All rights reserved.
 */
#ifndef VGA_H_INCLUDED
#define VGA_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

// The screen dimensions in standard VGA mode.
enum {
  VGA_WIDTH = 80,  // The width of the screen in characters.
  VGA_HEIGHT = 25  // The height of the screen in characters.
};

// VGA color constants.
enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15
};

// VGA error codes
enum {
  VGA_SUCCESS = 0,            // Success.
  VGA_NOT_INITIALIZED = 1,    // The VGA driver was not initialized.
  VGA_NOT_IMPLEMENTED = 2,    // The function is not implemented.
  VGA_INVALID_DIMENSION = 3,  // An invalid position / dimension was specified.
  VGA_INVALID_BUFFER = 4      // The caller's buffer pointer was NULL.
};

// Scroll directions
enum {
  VGA_SCROLL_UP = 0,
  VGA_SCROLL_DOWN = 1,
  VGA_SCROLL_LEFT = 2,
  VGA_SCROLL_RIGHT = 3
};

// Status type returned by VGA driver functions.
typedef int32_t vga_status_t;

// Initialize the VGA driver and clear the screen.
//
// Returns VGA_SUCCESS on success.
// Returns nonzero (theoretically) in the event of an error. See notes.
//
// Notes: At the present time, it is not possible for this function to return
// with an error. However, internally, it calls functions which can return
// errors under certain conditions. Additionally, it is possible that future
// enhancements to the initialization process could result in potential error
// conditions. In the interest of providing a consistent API, all functions
// in the library return a vga_status_t.
vga_status_t vga_init();

// Clear the screen buffer.
//
// Returns VGA_SUCCESS on success.
// Returns VGA_NOT_INITIALIZED if the driver is not initialized.
// RETURNS VGA_INVALID_DIMENSION if one or more dimensions are out of range.
//
// Notes: Clearing the screen is performed by filling the screen buffer with
// space characters that have a light grey foreground color and a black
// background color.
vga_status_t vga_clear();

// Draw a single character.
//
// Returns VGA_SUCCESS on success.
// Returns VGA_NOT_INITIALIZED if the driver is not initialized.
// Returns VGA_INVALID_DIMENSION if one or more dimensations are out of range.
vga_status_t vga_draw_char(size_t x, size_t y, uint8_t cp,
                           enum vga_color fgcolor, enum vga_color bgcolor);

// Draw a text string.
//
// Returns VGA_SUCCESS on success.
// Returns VGA_NOT_INITIALIZED if the driver is not initialized.
// Returns VGA_INVALID_DIMENSION if one or more dimensations are out of range.
//
// Notes: This function does not assume strings to be null terminated. It is
// the caller's responsibility to specify the number of characters to be drawn
// from 'str' by passing the length in 'len'.
//
// The function will "wrap" strings to the following line, with the exception
// that if wrapping would cause the text to lie outside the allowable range of
// the buffer, it will be truncated. No "scrolling" will occur.
vga_status_t vga_draw_text(size_t x, size_t y, const uint8_t* str, size_t len,
                           enum vga_color fgcolor, enum vga_color bgcolor);

// Fill a rectangle in the buffer with the specified code point, attributes.
//
// Returns VGA_SUCCESS on success.
// Returns VGA_NOT_INITIALIZED if the driver is not initialized.
// Returns VGA_INVALID_DIMENSION if one or more dimensions are out of range.
//
// Notes: The size of the display is VGA_WIDTH characters in width and
// VGA_HEIGHT characters in height. The 'x' parameter refers to a column on
// the display, while the y parameter refers to a row.
//
// The function will not attempt to perform a fill if any argument to the
// function is invalid; it will either perform the fill as requested or it
// will return an error without writing to the screen buffer.
vga_status_t vga_fill_rect(size_t x, size_t y, size_t width, size_t height,
                           uint8_t cp, enum vga_color fgcolor,
                           enum vga_color bgcolor);

// Scroll the screen in the specified direction. (See VGA_SCROLL_xx enums.)
//
// Returns VGA_SUCCESS on success.
// Returns VGA_NOT_INITIALIZED if the direction is not supported.
//
// Scrolling the screen causes the recently vacated line to be filled with
// the specified code point, foreground color, and background color.
//
// Notes: At the present time, only VGA_SCROLL_UP is supported.
vga_status_t vga_scroll(int direction, uint8_t cp, enum vga_color fgcolor,
                        enum vga_color bgcolor);

#endif  // VGA_H_INCLUDED
