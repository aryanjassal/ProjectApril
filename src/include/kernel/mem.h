#pragma once

#include <stddef.h>

// Fill a block of memory with a particular data
void *memset(void *dest, int val, size_t count);

// Fill a block of memory with a particular value a word at a time
void *memsetw(void *dest, int val, size_t count);

// Copy bytes from a block of memory and set the destination to the copied memory
void *memcpy(void *dest, const void *src, size_t count);