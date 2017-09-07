#include "arch/x86/src/x86.hpp"
#include "Arch.hpp"
#include "Console.hpp"

extern "C" {
    void kmain(void) {
        Arch *arch = x86::Arch::create();
        Console *console = arch->getConsole();
        char *notSupportedMsg;

        if(!arch->isSupported(&notSupportedMsg)) {
            console->setForeground(Console::Color::Red);
            console->printf("CPU not supported: %s", notSupportedMsg);
            arch->disableInterrupts();
            arch->halt();
        }

        arch->init();
    }
}
