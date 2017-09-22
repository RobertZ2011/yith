#include "memory.hpp"

void memcpy(void *dest, void *src, size_t size) {
    uint8_t *ptrd = (uint8_t*) dest;
    uint8_t *ptrs = (uint8_t*) src;

    for(size_t i = 0; i < size; i++) {
        *ptrd = *ptrs;
        ptrd++;
        ptrs++;
    }
}

template <>
void memset<uint8_t>(void *mem, uint8_t value, size_t count) {
    uint8_t *ptr = static_cast<uint8_t*>(mem);
    for(size_t i = 0; i < count; i++) {
        ptr[i] = value;
    }
}

template <>
void memset<uint16_t>(void *mem, uint16_t value, size_t count) {
    uint16_t *ptr = static_cast<uint16_t*>(mem);
    for(size_t i = 0; i < count; i++) {
        ptr[i] = value;
    }
}

int strcmp(const char *str1, const char *str2) {
    while(*str1 && *str2 && *str1++ == *str2++);

    if(!*str1 && !*str2) {
        return 0;
    }
    else
    if(*str1 > *str2) {
        return 1;
    }
    else {
        return -1;
    }
}
