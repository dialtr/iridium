#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "Building the kernel requires an appropriate i686 cross compiler."
#endif

#if !defined(__i386)
#error "Building the kernel requires an x86 elf compiler."
#endif

void kernel_main(void) {
  /* TODO(tdial): Implement */
}
