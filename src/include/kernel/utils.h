#include <stdint.h>

// Reverse the contents of a string
void *strrev(char str[], int length);

// Convert a decimal integer into a number of an arbitrary base
//! Note that negative numbers aren't handled yet
char *itoa(int num, char *str, int base);

// Fill a block of memory with a particular data
void *memset(void *dest, uint8_t val, uint32_t count);