#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stddef.h>

void memcpy(void *dest, void *src, size_t count);
void memset(void *mem, uint8_t value, size_t count);

#endif
