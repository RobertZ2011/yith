#ifndef ELF
#define ELF

#include "PageManager.hpp"
#include <stdint.h>

class Elf {
    PageManager *pageManager;
    uint32_t start;
public:
    enum class FileType : uint16_t {
        Relocatable = 1,
        Executable,
        Shared,
        Core
    };

    enum class ProgramType : uint32_t {
        Null = 0,
        Load,
    };

    enum class SectionType : uint32_t {
        Null = 0,
        ProgBits,
        SymTab,
        StrTab,
        Rela,
        Hash,
        Dynamic,
        Note,
        NoBits,
        Rel,
        ShLib,
        DynSym,
        InitArray,
        FiniArray,
        PreInitArray,
        Group,
        SymTabShndx,
        Num
    };

    enum class SectionAttr : uint64_t {
        Write = 0x01,
        Alloc = 0x02,
        Exec = 0x04,
    };

    enum class ISA : uint16_t {
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

    enum class ABI : uint8_t {
        System_V = 0x00,
        HP_UX = 0x01,
        NetBSD = 0x02,
        Linux = 0x03,
        GNUHurd = 0x04,
        Solaris = 0x06,
        AIX = 0x07,
        IRIX = 0x08,
        FreeBSD = 0x09,
        Tru64 = 0x0A,
        Modesto = 0x0B,
        OpenBSD = 0x0C,
        OpenVMS = 0x0D,
        NonStop = 0x0E,
        AROS = 0x0F,
        Fenix = 0x10,
        CloudABI = 0x11,
        Sortix = 0x53
    };

    struct FileHeader {
        uint8_t magic[4];
        uint8_t bitSize;
        uint8_t endianess;
        uint8_t version;
        ABI abi;
        uint8_t abiVersion;
        uint8_t padding[7];
        FileType type;
        ISA isa;
        uint32_t longVersion;
        uint64_t entry;
        uint64_t phoff;
        uint64_t shoff;
        uint32_t flags;
        uint16_t ehsize;
        uint16_t phentsize;
        uint16_t phnum;
        uint16_t shentsize;
        uint16_t shnum;
        uint16_t shstrndx;
    } __attribute__((packed));

    struct ProgramHeader {
        ProgramType type;
        uint32_t flags;
        uint64_t offset;
        uint64_t vaddr;
        uint64_t paddr;
        uint64_t filesz;
        uint64_t memsz;
        uint64_t align;
    } __attribute__((packed));

    struct SectionHeader {
        uint32_t name;
        SectionType type;
        SectionAttr attrs;
        uint64_t addr;
        uint64_t offset;
        uint64_t size;
        uint32_t link;
        uint32_t info;
        uint64_t addralign;
        uint64_t entsize;
    } __attribute__((packed));

    Elf(PageManager&);

    bool load(void*, const char **err);
    uint32_t getStart(void);
};

uint64_t operator&(Elf::SectionAttr, Elf::SectionAttr);
#endif
