/*
 * console.h
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

// This header file defines a console structure and related function types
// that are implemented by all console devices (terminal screens, serial
// port consoles, etc.) The kernel will have access to the head of a linked
// list of console objects; writing to console devices will iterating through
// the chain of console devices and calling console_write() on each one.

#include <stddef.h>

// All consoles implement a function of this type.
//   self: Pointer to console structure.
//   buf:  Buffer of characters to write.
//   len:  Number of valid characters in the buffer.
// Returns the number of bytes transferred to the console.
typedef size_t (*console_write)(void* self, const void* buf, size_t len);

// All console structure implementations *must* start with the same layout
// as the structure below. They *may* (and most probably will) contain
// additional variables to hold state information.
struct console {
  struct console* next;  // Pointer to next console in list.
  console_write write;   // Implementation of the write function.
};

#endif  // CONSOLE_H_INCLUDED
