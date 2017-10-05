#![feature(lang_items)]
#![feature(asm)]
#![no_std]

extern crate rlibc;

pub mod console_trait;
pub mod arch_trait;
mod arch;

pub use arch::x86::isr::isr_handler;
use console_trait::Console;

#[no_mangle]
pub extern fn kmain() {
    let mut c = arch::x86::console::Console::new();
    c.clear();
    c.print("The Great Kernel of Yith");
}

#[lang = "eh_personality"] extern fn eh_personality() {}
#[lang = "panic_fmt"] #[no_mangle] pub extern fn panic_fmt() -> ! {loop{}}
