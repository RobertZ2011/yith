#include "PageManager.hpp"
#include "Arch.hpp"
#include "../../../memory.hpp"

namespace x86 {
    const int PageManager::PageSize = 2 * 1024 * 1024;
    PageManager pageManagerInstance;

    ::PageManager& PageManager::getInstance(void) {
        return pageManagerInstance;
    }

    void PageManager::init(::Arch& arch, Multiboot2Info& info) {
        uint32_t gig;
        uint32_t pdpt = reinterpret_cast<uint32_t>(&this->pdpt[0]);
        uint32_t end = reinterpret_cast<uint32_t>(&kernelEnd);
        auto module = info.getTag<Multiboot2Info::Type::Module>();
        uint32_t allocatedPages;
        uint32_t totalPages;

        //find the end of used pages
        while(module) {
            if(module->end > end) {
                end = module->end;
            }

            module = info.getTag<Multiboot2Info::Type::Module>(module);
        }

        this->arch = reinterpret_cast<Arch*>(&arch);

        memset<uint8_t>(&this->pml4, 0, sizeof(HigherEntry) * 512);
        memset<uint8_t>(&this->pdpt, 0, sizeof(HigherEntry) * 512);
        memset<uint8_t>(&this->gigs[0], 0, sizeof(DirectoryEntry) * 512);
        memset<uint8_t>(&this->gigs[1], 0, sizeof(DirectoryEntry) * 512);
        memset<uint8_t>(&this->gigs[2], 0, sizeof(DirectoryEntry) * 512);
        memset<uint8_t>(&this->gigs[3], 0, sizeof(DirectoryEntry) * 512);

        this->pml4[0].type = 0x3;
        this->pml4[0].addr = pdpt >> 12;

        for(int count = 0; count < 4; count++) {
            gig = reinterpret_cast<uint32_t>(&this->gigs[count][0]);
            this->pdpt[count].type = 0x3;
            this->pdpt[count].addr = gig >> 12;
        }

        //map available memory
        totalPages = 64;
        /*totalPages = / PageManager::PageSize;
        if( & 0xFFFFF) {
            totalPages++;
        }*/

        for(uint32_t count = 0; count < totalPages; count++) {
            uint32_t nextPage = count * PageManager::PageSize;
            this->mapAddress(nextPage, nextPage);
        }

        //mark the kernel as allocated
        allocatedPages = end / PageManager::PageSize;
        if(allocatedPages * PageManager::PageSize < end) {
            allocatedPages++;
        }

        for(uint32_t count = 0; count < allocatedPages; count++) {
            this->markAllocated(count * PageManager::PageSize);
        }
    }

    void *PageManager::allocPages(size_t pages) {
        uint32_t ptr = 0;
        size_t foundPages = 0;

        for(int pageDir = 0; pageDir < 4; pageDir++) {
            for(int entry = 0; entry < 512; entry++) {
                if((this->gigs[pageDir][entry].type & 0x01) && !this->gigs[pageDir][entry].allocated) {
                    if(foundPages == 0) {
                        ptr = this->gigs[pageDir][entry].addr << 21;
                        foundPages = 1;
                    }
                    else {
                        foundPages++;
                    }

                    if(foundPages == pages) {
                        //I know, goto is pure evil
                        goto loopBreak;
                    }
                }
                else {
                    ptr = 0;
                    foundPages = 0;
                }
            }
        }

        //unable to find a page
        return nullptr;

loopBreak:
        for(size_t count = 0; count < pages; count++) {
            this->markAllocated(ptr + count * PageManager::PageSize);
        }

        return reinterpret_cast<void*>(ptr);
    }

    void PageManager::freePages(void *ptr, size_t pages) {
        uint32_t addr = reinterpret_cast<uint32_t>(ptr);
        uint8_t pdptIndex = addr >> 30;
        uint16_t pageDirIndex = (addr >> 21) & 0x1FF;

        for(int pageDir = pdptIndex; pageDir < 4; pageDir++) {
            for(int entry = pageDirIndex; entry < 512; entry++) {
                this->gigs[pageDir][entry].allocated = 0;
            }
        }
    }

    void PageManager::markAllocated(uint32_t addr) {
        uint8_t pdptIndex = addr >> 30;
        uint16_t pageDirIndex = (addr >> 21) & 0x1FF;
        DirectoryEntry *pageDir;

        pageDir = reinterpret_cast<DirectoryEntry*>(this->pdpt[pdptIndex].addr << 12);
        pageDir[pageDirIndex].allocated = 1;
    }

    void PageManager::mapAddress(uint32_t virt, uint32_t physical) {
        uint8_t pdptIndex = virt >> 30;
        uint16_t pageDirIndex = (virt >> 21) & 0x1FF;
        DirectoryEntry *pageDir;

        pageDir = reinterpret_cast<DirectoryEntry*>(this->pdpt[pdptIndex].addr << 12);
        pageDir[pageDirIndex].type = 0x83;
        pageDir[pageDirIndex].addr = physical >> 21;
    }

    void PageManager::enableTranslation(void) {
        uint32_t cr3 = reinterpret_cast<uint32_t>(&this->pml4[0]);
        uint32_t ia32_efer;

        this->arch->disableInterrupts();
        ia32_efer = this->arch->readMSR(Arch::MSR::IA32_EFER);
        ia32_efer |= 0x100;
        this->arch->writeMSR(Arch::MSR::IA32_EFER, ia32_efer);

        cr3 = reinterpret_cast<uint32_t>(&this->pml4[0]);
        asm volatile(
            "mov %%cr4, %%eax\n"
            "orl $0x20, %%eax\n"
            "mov %%eax, %%cr4\n"
            "mov %0, %%cr3\n"
            "mov %%cr0, %%eax\n"
            "orl $0x80000000, %%eax\n"
            "mov %%eax, %%cr0\n" :
            :
            "r"(cr3) :
            "eax"
        );
        this->arch->enableInterrupts();
    }

    size_t PageManager::getPageSize(void) {
        return PageManager::PageSize;
    }
}
