# Milestone Journal

* 2018-09-30 T 04:05:00

  Milestone 3 ("VGA Display Routines") has been reached. Routines for
  drawing single characters as well as text strings to the screen buffer
  are now part of the vga function library. The "Hello, Iridium!" message
  is drawn at the lower-left portion of the screen, demonstrating
  vga_draw_text()'s ability to place strings in any location. 

* 2018-09-29 T 17:01:00

  VGA display driver complete. Supports drawing filled rectangles with a
  selected fill character and foreground, background color attribute.
  This was required to implement the vga_clear() routine. Next steps are
  to write a few support routines for drawing text strings.

* 2018-09-29 T 02:38:00

  ISO target now builds. Tested with QEMU and it seems to boot!

* 2018-09-29 T 02:17:00
  
  Image is now building.

* 2018-09-29 T 02:17:00

  Completed work on the the **bootstrap** script. It successfully pulls
  down the necessary source and buildson Ubuntu 18.04. There are still
  some build errors to track down that don't appear to affect the
  ability to build/install binutils and the gcc cross compiler. The
  script is not really that robust at this time.
