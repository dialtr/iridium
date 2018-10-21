/*
 * vga_terminal.h
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */
#ifndef VGA_TERMINAL_H_INCLUDED
#define VGA_TERMINAL_H_INCLUDED

#include "console.h"

// Initialize the main terminal; return a generic console pointer.
struct console* vga_terminal_init();

#endif  // VGA_TERMINAL_H_INCLUDED
