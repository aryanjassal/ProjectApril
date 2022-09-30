#include "io/string.h"
#include <stddef.h>
#include <stdint.h>

// Reverse the contents of a string
void *strrev(char *str, int length) {
  // Declare some variables that will be useful in the reversal
  int start = 0;
  int end = length - 1;

  // Actual loop to flip the string
  while (start < end) {
    // Swap the values at <start> and <end>
    char temp = *(str + start);
    *(str + start) = *(str + end);
    *(str + end) = temp;

    // Increment start and decrement end to point to the next pair of characters
    start++;
    end--;
  }

  // Return statement to keep the compiler happy
  return NULL;
}

// Returns the length of the string provided
size_t strlen(const char *str) {
  size_t len = 0;
  
  while (*str != '\0') {
    len++;
    str++;
  }
  return len;
}

// Appends the source string to the destination string
char *strcat(char *destination, const char *source) {
  // char *ptr = destination + strlen(destination);
  // How ugly
  // TODO: make a better and more elegant looking solution
  uint32_t i = 0, j = 0;
  for (; destination[i] != '\0'; i++);

  for (; source[j] != 0; j++) {
    destination[i + j] = source[j];
  }

  // Null-terminate the string
  destination[i + j] = '\0';
  return destination;
}

// Copy the string from the source into the destination location
char *strcpy(char *destination, const char *source) {
  for(size_t i = 0; (destination[i] = source[i]) != '\0'; i++);
  return destination;
}

// Convert an unsigned decimal integer into a string number of an arbitrary base
char *utoa(int num, char *buf, int base) {
  int i = 0;

  // Handle 0 explicitly
  if (num == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return buf;
  }

  // Process individual digits
  while (num != 0) {
    int rem = num % base;
    buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num /= base;
  }

  // Reverse the string (because the digits are processed in reverse order)
  strrev(buf, i);

  // Append the null terminator at the end of the string
  buf[i] = '\0';

  // Return the properly reversed, null terminated string
  return buf;
}