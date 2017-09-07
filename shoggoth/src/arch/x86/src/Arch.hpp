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

        Arch(void);

        static Arch *create(void);

        void init(void);
        ::Console *getConsole(void);
        bool isSupported(char **err);
        void disableInterrupts(void);
        void enableInterrupts(void);
        void halt(void);
    };
}
#endif
