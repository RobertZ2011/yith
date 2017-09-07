#include "memory.hpp"

void memcpy(void *dest, void *src, size_t count) {
    uint8_t *ptrd = static_cast<uint8_t*>(dest);
    uint8_t *ptrs = static_cast<uint8_t*>(src);

    for(size_t i = 0; i < count; i++) {
        *ptrd = *ptrs;
        ptrd++;
        ptrs++;
    }
}

void memset(void *mem, uint8_t value, size_t count) {
    uint8_t *ptr = static_cast<uint8_t*>(mem);
    for(size_t i = 0; i < count; i++) {
        ptr[i] = value;
    }
}
