#include "arch/x86/src/x86.hpp"
#include "Arch.hpp"
#include "Console.hpp"
#include "SothothInfo.hpp"
#include "PageManager.hpp"
#include "Elf.hpp"
#include "multiboot2.hpp"

extern "C" {
    void kmain(uint32_t bootMagic, Multiboot2::Info& multibootInfo, SothothInfo& sothothInfo) {
        Arch& arch = x86::Arch::getInstance();
        Console& console = arch.getConsole();
        PageManager& pageManager = arch.getPageManager();
        Elf sothoth(pageManager);
        char *notSupportedMsg;
        void *page;

        console.clear();
        console.print("The humble Shoggoth loader\n");

        if(!arch.isSupported(&notSupportedMsg)) {
            console.setForeground(Console::Color::Red);
            console.printf("CPU not supported: %s", notSupportedMsg);
            arch.disableInterrupts();
            arch.halt();
        }

        arch.init();

        console.print("Setting up page management\n");
        pageManager.init(arch);

        console.print("Enabling address translation\n");
        pageManager.enableTranslation();

        console.print("Enabling 64 bit mode\n");
        arch.enable64Bit();

        arch.disableInterrupts();
        arch.halt();
    }
}
