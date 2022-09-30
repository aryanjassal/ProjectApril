#pragma once

#include <stdint.h>
#include <stddef.h>

// Reverse the contents of a string
void *strrev(char str[], int length);

// Returns the length of the string provided
size_t strlen(const char *str);

// Appends the source string to the destination string
char *strcat(char *destination, const char *source);

// Copy the string source into the destination location
char *strcpy(char *destination, const char *source);

// Convert an unsigned decimal integer into a numeric string with an arbitrary base
char *utoa(int num, char *buf, int base);