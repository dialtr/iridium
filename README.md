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

1. **Cross Compiler** - Completed work on a bootstrap script that is
   able to fetch the necessary sources from the internet to build an
   appropriate cross compiler. The milestone version will be tested on
   Ubuntu 18.04.

2. **First Boot** - A multiboot-compliant image of the system can boot
   from GRUB. Control transfers from the boot loader to an entry point
   written in the C programming language, and "Hello, Iridium!" is
   displayed in the terminal prior to halting.
   
3. **VGA Display Routines** - A set of routines for performing basic
   character output on the screen using color mode VGA. The hello
   message will be displayed in color.
   
4. **Basic Keyboard Support** - The system supports basic keyboard
   input. Pressing alphanumeric keys will result in the corresponding
   letters to be displayed on the screen using the VGA routines
   developed for the second milestone.

## Pending Tasks

* HIGH - Test whether the bootstrap script works on Ubuntu 18.04
* LOW - Test whether the bootstrap script works on Debian
* LOW - Test whether the bootstrap script works on Ubuntu 16.04

## Package Dependencies

TODO(tdial): Document the build environment/setup.

* Ubuntu 18.04 (And possibly 16.04)
  * build-essential
  * binutils
  * bison
  * make
  * flex
  * libgmp3-dev
  * libmpfr-dev
  * texinfo
  * libmpc-dev
  * libisl-dev
  * libcloog-isl-dev
  * ncurses-dev
  
* Download Source
  * **binutils** - https://ftp.gnu.org/gnu/binutils/binutils-2.30.tar.gz
  * **gcc** - https://ftp.gnu.org/gnu/gcc/gcc-4.7.3/gcc-4.7.3.tar.gz

## Resources

* https://wiki.osdev.org/GCC_Cross-Compiler
* https://wiki.osdev.org/Bare_Bones

TODO(tdial): Document the build process.

## Author

Thomas R. Dial <dialtr@gmail.com>


