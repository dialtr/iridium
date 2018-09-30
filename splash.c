/*
 * splash.c
 *
 * Copyright (C) 2018 The iridium authors
 * All Rights Reserved
 */

#include "splash.h"
#include "vga.h"

void display_splash_screen() {
  const uint8_t E = 32;   // Empty
  const uint8_t M = 177;  // Medium shaded block
  const uint8_t S = 219;  // Solid block

  const uint8_t banner_text[13][14] = {
      {S, S, S, S, S, S, S, S, S, S, S, S, S, S},
      {S, E, E, E, E, E, E, E, E, E, E, E, E, S},
      {S, E, E, E, E, E, E, E, E, E, E, E, E, S},
      {S, E, M, M, M, M, M, E, E, E, E, E, E, S},
      {S, E, E, E, M, E, E, E, E, E, E, E, E, S},
      {S, E, E, E, M, E, E, E, M, E, M, M, E, S},
      {S, E, E, E, M, E, E, E, M, M, E, E, E, S},
      {S, E, E, E, M, E, E, E, M, E, E, E, E, S},
      {S, E, E, E, M, E, E, E, M, E, E, E, E, S},
      {S, E, M, M, M, M, M, E, M, E, E, E, E, S},
      {S, E, E, E, E, E, E, E, E, E, E, E, E, S},
      {S, E, E, E, E, E, E, E, E, E, E, E, E, S},
      {S, S, S, S, S, S, S, S, S, S, S, S, S, S}};

  // First, reset to dark grey background.
  vga_fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, E, VGA_COLOR_WHITE,
                VGA_COLOR_DARK_GREY);

  // The upper-left position to draw the banner.
  const uint8_t x_off = 26;
  const uint8_t y_off = 6;

  // Draw the banner.
  for (size_t y = 0; y < 13; ++y) {
    for (size_t x = 0; x < 14; ++x) {
      for (size_t t = 0; t < 2; ++t) {
        vga_draw_char(x_off + (x * 2) + t, y_off + y, banner_text[y][x],
                      VGA_COLOR_LIGHT_GREY, VGA_COLOR_DARK_GREY);
      }
    }
  }
}
