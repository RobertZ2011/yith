#ifndef MULTIBOOT2
#define MULTIBOOT2

#include <stdint.h>

namespace Multiboot2 {
    enum class TagType : uint32_t {
        BasicMemory = 4
    };

    struct Info {
        uint32_t size;
        uint32_t reserved;
    };

    struct BasicMemory {
        uint32_t memLower;
        uint32_t memUpper;
    };
}

#endif
