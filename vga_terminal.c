/*
 * vga_terminal.c
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */
#include "vga_terminal.h"

struct vga_terminal {
  // Console fields: identical in layout to struct console.
  struct console* next;
  console_write write;
};

static struct vga_terminal g_term;

static size_t vga_terminal_write(void* self, const void* buf, size_t len) {
  struct vga_terminal* term = (struct vga_terminal*)self;
  if (!term) {
    return -1;
  }

  (void)buf;
  (void)len;

  return 0;
}

// Initialize the main terminal; return a generic console pointer.
struct console* vga_terminal_init() {
  g_term.next = 0;
  g_term.write = vga_terminal_write;

  return (struct console*)&g_term;
}
