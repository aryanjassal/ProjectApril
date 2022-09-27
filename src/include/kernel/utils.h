#include <stdint.h>

// Reverse the contents of a string
void *strrev(char str[], int length);

// Returns the length of the string provided
uint16_t strlen(const char *str);

// Appends the source string to the destination string
char *strcat(char *destination, const char* source);

// Convert a decimal integer into a number of an arbitrary base
//! Note that negative numbers aren't handled yet
char *itoa(int num, char *str, int base);

// Fill a block of memory with a particular data
void *memset(void *dest, uint8_t val, uint32_t count);

// Permanently halt the computer
void halt();