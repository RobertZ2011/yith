#ifndef PAGE_MANAGER
#define PAGE_MANAGER

#include <stddef.h>
#include <stdint.h>

#include "Multiboot2Info.hpp"

class Arch;

class PageManager {
public:
    virtual void init(Arch&, Multiboot2Info&) = 0;
    virtual void *allocPages(size_t pages) = 0;
    virtual void freePages(void*, size_t pages) = 0;
    virtual void markAllocated(uint32_t addr) = 0;
    virtual void mapAddress(uint32_t virt, uint32_t physical) = 0;
    virtual void enableTranslation(void) = 0;
    virtual size_t getPageSize(void) = 0;
};

#endif
