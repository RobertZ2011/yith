#include "Elf.hpp"
#include "memory.hpp"

Elf::Elf(PageManager& pageManager) {
    this->pageManager = &pageManager;
}

bool Elf::load(void *ptr, const char **err) {
    FileHeader *fileHeader = static_cast<FileHeader*>(ptr);
    ProgramHeader *programHeaders;
    SectionHeader *sectionHeaders;
    uint32_t startAddress = 0xFFFFFFFF;
    uint32_t endAddress = 0;
    uint32_t loadedSize = 0;
    uint32_t phoff;
    uint32_t shoff;
    size_t pages;
    size_t pageSize = this->pageManager->getPageSize();
    uint32_t allocatedPages;

    if(fileHeader->magic[0] != 0x7F ||
       fileHeader->magic[1] != 'E' ||
       fileHeader->magic[2] != 'L' ||
       fileHeader->magic[3] != 'F') {
           *err = "ELF magic number doesn't match";
           return false;
    }

    if(fileHeader->abi != ABI::System_V) {
        *err = "Unsupported ABI";
        return false;
    }

    if(fileHeader->type != FileType::Executable) {
        *err = "Not executable";
        return false;
    }

    if(fileHeader->isa != ISA::x86_64) {
        *err = "Wrong ISA";
        return false;
    }

    if(fileHeader->entry >> 32) {
        *err = "Entry address exceeds 32 bit space";
        return false;
    }
    this->start = fileHeader->entry;

    if(fileHeader->phentsize != sizeof(ProgramHeader)) {
        *err = "Program header structure does not have proper size";
        return false;
    }

    if(fileHeader->phoff >> 32) {
        *err = "Program header exceeds 32 bit capabilities";
        return false;
    }

    if(fileHeader->shentsize != sizeof(SectionHeader)) {
        *err = "Section header structure does not have proper size";
        return false;
    }

    if(fileHeader->shoff >> 32) {
        *err = "Section header exceeds 32 bit capabilities";
        return false;
    }

    phoff = (uint32_t) fileHeader->phoff;
    programHeaders = reinterpret_cast<ProgramHeader*>((uint8_t*)ptr + phoff);

    //find the start and end address of the loaded program
    for(uint32_t i = 0; i < fileHeader->phnum; i++) {
        if(programHeaders[i].type == ProgramType::Load) {
            if(programHeaders[i].vaddr < startAddress) {
                startAddress = programHeaders[i].vaddr;
            }

            if(programHeaders[i].vaddr + programHeaders[i].memsz > endAddress) {
                endAddress = programHeaders[i].vaddr + programHeaders[i].memsz;
            }
        }
    }

    //get the number of pages required
    loadedSize = endAddress - startAddress;
    pages = loadedSize / pageSize;

    //make sure we're not a page short
    if(pages * pageSize < loadedSize) {
        pages++;
    }

    allocatedPages = reinterpret_cast<uint32_t>(this->pageManager->allocPages(pages));
    if(!allocatedPages) {
        *err = "Failed to allocate memory";
        return false;
    }

    memset<uint8_t>(reinterpret_cast<void*>(allocatedPages), 0, pages * pageSize);

    for(size_t page = 0; page < pages; page++) {
        this->pageManager->mapAddress(startAddress + page * pageSize, allocatedPages + page * pageSize);
    }

    shoff = (uint32_t) fileHeader->shoff;
    sectionHeaders = reinterpret_cast<SectionHeader*>((uint8_t*)ptr + shoff);

    for(uint32_t i = 0; i < fileHeader->shnum; i++) {
        if(sectionHeaders[i].type == SectionType::ProgBits && sectionHeaders[i].attrs & SectionAttr::Alloc) {
            memcpy(reinterpret_cast<void*>(sectionHeaders[i].addr), (uint8_t*)ptr + sectionHeaders[i].offset, sectionHeaders[i].size);
        }
    }

    return true;
}

uint32_t Elf::getStart(void) {
    return this->start;
}

uint64_t operator&(Elf::SectionAttr left, Elf::SectionAttr right) {
    return static_cast<uint64_t>(left) & static_cast<uint64_t>(right);
}
