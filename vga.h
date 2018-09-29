/*
 * vga.h
 *
 * Copyright (C) 2018 The iridium authors.
 * All rights reserved.
 */
#ifndef VGA_H_INCLUDED
#define VGA_H_INCLUDED

#include <stdint.h>
#include <stddef.h>


// The screen dimensions in standard VGA mode.
enum {
  VGA_WIDTH = 80,
	VGA_HEIGHT = 25
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
	VGA_SUCCESS = 0,
	VGA_NOT_INITIALIZED = 1,
	VGA_INVALID_DIMENSION = 2
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
vga_status_t vga_fill_rect(size_t x,
		                       size_t y,
									         size_t width,
									         size_t height,
									         unsigned char cp,
									         enum vga_color fgcolor,
									         enum vga_color bgcolor);

#endif  // VGA_H_INCLUDED
