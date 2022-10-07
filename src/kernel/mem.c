#include "mem.h"
#include <stdint.h>
#include <stddef.h>

// Fill a block of memory with a particular data
void *memset(void *dest, int val, size_t count) {
  // Cast the destination pointer from void to an 8-bit value
  uint8_t *actual_dest = (uint8_t *)dest;

  // Actual loop to modify memory
  for (size_t i = 0; i < count; i++) {
    actual_dest[i] = val;
  }

  // Return the destination pointer as part of the original function
  return dest;
}

// Fill a block of memory with a particular value a word at a time
void *memsetw(void *dest, int val, size_t count) {
  // Cast the destination pointer from void to a 16-bit word value
  uint16_t *actual_dest = (uint16_t *)dest;

  // Actual loop to modify memory
  for (size_t i = 0; i < count; i++) {
    actual_dest[i] = val;
  }

  // Return the destination pointer as part of the original function
  return dest;
}

// Copy bytes from a block of memory and set the destination to the copied memory
void *memcpy(void *dest, const void *src, size_t count) {
  // Cast the void pointers to byte-aligned pointers
  uint8_t *actual_dest = (uint8_t *)dest;
  uint8_t *actual_src = (uint8_t *)src;

  // Actual copy loop
  for (size_t i = 0; i < count; i++) {
    actual_dest[i] = actual_src[i];
  }

  // Return the destination pointer as required by the C standard
  return dest;
}

// Move bytes from a block of memory to another one (overlap-safe)
void *memmove(void *dest, const void *src, size_t count) {
  // Cast the void pointers to byte-aligned pointers
  uint8_t *actual_dest = (uint8_t *)dest;
  uint8_t *actual_src = (uint8_t *)src;

  // Create an array which is a clone of the source
  uint8_t data_clone[sizeof(uint8_t) * count];

  // Clone the data from src into the temporary array
  for (size_t i = 0; i < count; i++) {
    data_clone[i] = actual_src[i];
  }

  // Now move the data from the temporary clone array into destination address
  for (size_t i = 0; i < count; i++) {
    actual_dest[i] = data_clone[i];
  }

  // Return the destination pointer as required by the C standard
  return dest;
}