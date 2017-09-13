#ifndef PAGE_MANAGER
#define PAGE_MANAGER

#include <stddef.h>
#include <stdint.h>

class Arch;

class PageManager {
public:
    virtual void init(Arch&) = 0;
    virtual void *allocPages(size_t pages) = 0;
    virtual void freePages(void*, size_t pages) = 0;
    virtual void markAllocated(uint32_t addr) = 0;
    virtual void mapAddress(uint32_t virt, uint32_t physical) = 0;
    virtual void enableTranslation(void) = 0;
    virtual size_t getPageSize(void) = 0;
};

#endif
