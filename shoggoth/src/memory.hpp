#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stddef.h>

void memcpy(void *dest, void *src, size_t count);

template <typename T>
void memset(void *mem, T value, size_t count);

template <>
void memset<uint8_t>(void *mem, uint8_t value, size_t count);

template <>
void memset<uint16_t>(void *mem, uint16_t value, size_t count);

int strcmp(const char *, const char *);

#endif
