#include "arch/x86/src/x86.hpp"
#include "Arch.hpp"
#include "Console.hpp"
#include "SothothInfo.hpp"
#include "PageManager.hpp"
#include "Elf.hpp"
#include "Multiboot2Info.hpp"
#include "memory.hpp"

extern "C" {
    void kmain(uint32_t bootMagic, Multiboot2Info& multibootInfo, SothothInfo& sothothInfo) {
        Arch& arch = x86::Arch::getInstance();
        Console& console = arch.getConsole();
        PageManager& pageManager = arch.getPageManager();
        Elf sothoth(pageManager);
        const char *errMsg;

        console.clear();
        console.print("The humble Shoggoth loader\n");

        if(bootMagic != Multiboot2Info::MagicNumber) {
            console.setForeground(Console::Color::Red);
            console.printf("Cannot load, multiboot2 magic number is %x instead of %x", bootMagic, Multiboot2Info::MagicNumber);
            arch.disableInterrupts();
            arch.halt();
        }

        if(!arch.isSupported(&errMsg)) {
            console.setForeground(Console::Color::Red);
            console.printf("CPU not supported: %s", errMsg);
            arch.disableInterrupts();
            arch.halt();
        }

        arch.init(multibootInfo);

        console.print("Setting up page management\n");
        pageManager.init(arch, multibootInfo);

        console.print("Loading payload\n");
        //find the sothoth module
        auto module = multibootInfo.getTag<Multiboot2Info::Type::Module>();
        while(module) {
            if(strcmp(reinterpret_cast<char*>(&module->stringStart), "--boot-payload") == 0) {
                break;
            }

            module = multibootInfo.getTag<Multiboot2Info::Type::Module>(module);
        }

        if(!module) {
            console.setForeground(Console::Color::Red);
            console.printf("No payload found\n");
            arch.disableInterrupts();
            arch.halt();
        }

        console.printf("Payload at %x\n", module->start);

        console.print("Enabling address translation\n");
        pageManager.enableTranslation();

        if(!sothoth.load(reinterpret_cast<void*>(module->start), &errMsg)) {
            console.setForeground(Console::Color::Red);
            console.printf("Failed to load boot payload: %s\n", errMsg);
            arch.disableInterrupts();
            arch.halt();
        }

        sothothInfo.main = reinterpret_cast<void*>(sothoth.getStart());
        console.printf("entry at %x\n", sothoth.getStart());

        console.print("Enabling 64 bit mode\n");
        arch.enable64Bit();

        arch.disableInterrupts();
    }
}
