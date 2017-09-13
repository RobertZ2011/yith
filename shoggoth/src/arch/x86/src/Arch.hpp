#ifndef ARCH_X86
#define ARCH_X86

#include "../../../Arch.hpp"
#include "Console.hpp"

namespace x86 {
    class Arch : public ::Arch {
    public:
        enum class CpuidFunc : uint32_t {
            VendorID = 0,
            ProcessorInfo,
            CacheTLBInfo,
            SerialNumber,
            HighestFunction = 0x80000000,
            ExtProcessorInfo
        };

        enum class MSR : uint32_t {
            IA32_EFER = 0xC0000080
        };

        Arch(void);

        static Arch& getInstance(void);

        void init(void);
        ::Console& getConsole(void);
        ::PageManager& getPageManager(void);
        bool isSupported(char **err);
        void disableInterrupts(void);
        void enableInterrupts(void);
        void halt(void);
        void enable64Bit(void);

        uint64_t readMSR(MSR msr);
        void writeMSR(MSR msr, uint64_t value);

        void outb(uint16_t port, uint8_t value);
    };
}
#endif
