#include "utils.h"
#include <stdint.h>

// Reverse the contents of a string
void *strrev(char str[], int length) {
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
}

// Convert a decimal integer into a number of an arbitrary base
char *itoa(int num, char *str, int base) {
  int i = 0;

  // Handle 0 explicitly
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // Process individual digits
  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num /= base;
  }

  // Reverse the string (because the digits are processed in reverse order)
  strrev(str, i);

  // Append the null terminator at the end of the string
  str[i] = '\0';

  // Return the properly reversed, null terminated string
  return str;
}

// Fill a block of memory with a particular data
void *memset(void *dest, uint8_t val, uint32_t count) {
  // Cast the destination pointer from void to an 8-bit value
  uint8_t *actual_dest = (uint8_t *)dest;

  // Actual loop to modify memory
  for (uint32_t i = 0; i < count; i++) {
    *actual_dest++ = val;
  }
}