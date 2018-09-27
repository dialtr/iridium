# Iridium Operating System

## About

The goal of this project is to design and implement a minimal operating
system. I have no lofty ambitions for the system: it is merely a means
for me to learn more about operating systems, an area that has always
interested me personally.

## Goals

* **Understandable** - I will strive to make the system easy to
  understand so that it may be used as a reference for others who are
  trying to learn operating system concepts. Except where absolutely
  crucial, performance will be sacrificed for the sake of simplicity.
  
* **Readable** - I will fully document the system, including notes on
  its design, as well as implementation notes in the form of source
  comments.

* **Compatible** - Iridium will aim to provide a UNIX-like environment
  so that it is familiar to those who may be interested in
  experimenting or enhancing the system. 
 
* **Bootable** - The system will be capable of booting on actual
  hardware. Initial development, however, will be done on QEMU, in
  order to accelerate development.

## Project Milestones

1. **First Boot** - A multiboot-compliant image of the system can boot
   from GRUB. Control transfers from the boot loader to an entry point
   written in the C programming language, and "Hello, Iridium!" is
   displayed in the terminal prior to halting.
   
2. **VGA Display Routines** - A set of routines for performing basic
   character output on the screen using color mode VGA. The hello
   message will be displayed in color.
   
3. **Basic Keyboard Support** - The system supports basic keyboard
   input. Pressing alphanumeric keys will result in the corresponding
   letters to be displayed on the screen using the VGA routines
   developed for the second milestone.
   
## Building

TODO(tdial): Document the build environment/setup.
TODO(tdial): Document the build process.

## Author

Thomas R. Dial <dialtr@gmail.com>


