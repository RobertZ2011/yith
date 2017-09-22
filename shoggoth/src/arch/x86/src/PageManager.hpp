#ifndef X86_PAGE_MANAGER
#define X86_PAGE_MANAGER

#include "../../../PageManager.hpp"
#include <stdint.h>

extern uint8_t kernelEnd;

namespace x86 {
    class Arch;
    class PageManager : public ::PageManager {
        struct HigherEntry { //covers PML4 and PDPT
            uint8_t type;
            uint8_t ignored1 : 4;
            uint64_t addr : 40;
            uint16_t ignored2 : 11;
            uint8_t xd : 1;
        } __attribute__((packed));

        static_assert(sizeof(HigherEntry) == 8, "Higher paging structures are not 64 bits");

        struct DirectoryEntry { //2MB pages
            uint8_t type;
            uint8_t global : 1;
            uint8_t allocated : 3;
            uint8_t pat : 1;
            uint8_t reserved : 8;
            uint32_t addr : 31;
            uint8_t ignored : 7;
            uint8_t pk : 4;
            uint8_t xd : 1;
        } __attribute__((packed));

        static_assert(sizeof(DirectoryEntry) == 8, "DirectoryEntry structure is not 64 bits");


        HigherEntry pml4[512] __attribute__((aligned(4096)));
        HigherEntry pdpt[512] __attribute__((aligned(4096)));
        DirectoryEntry gigs[4][512] __attribute__((aligned(4096)));

        Arch *arch;

        static const int PageSize;

    public:
        static ::PageManager& getInstance(void);
        void init(::Arch&, Multiboot2Info&);
        void *allocPages(size_t pages);
        void freePages(void *ptr, size_t pages);
        void markAllocated(uint32_t);
        void mapAddress(uint32_t virt, uint32_t physical);
        void enableTranslation(void);
        size_t getPageSize(void);
    };
}

#endif
