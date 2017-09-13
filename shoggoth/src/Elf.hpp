#ifndef ELF
#define ELF

#include "PageManager.hpp"
#include <stdint.h>

class Elf {
    struct FileHeader {
        uint32_t magic;
    } __attribute__((packed));

    struct ProgramHeader {

    } __attribute__((packed));

    enum class FileType : uint8_t {
        Relocatable = 1,
        Executable,
        Shared,
        Core
    };

    enum class ISA : uint8_t {
        None = 0x00,
        SPARC = 0x02,
        x86 = 0x03,
        MIPS = 0x08,
        PowerPC = 0x14,
        S390 = 0x16,
        ARM = 0x28,
        SuperH = 0x2A,
        IA64 = 0x32,
        x86_64 = 0x3E,
        AArch64 = 0xB7,
        RISC_V = 0xF3
    };

    PageManager& pageManager;

public:
    Elf(PageManager&);

    void load(void*);
    uint32_t getStart(void);
};
#endif
