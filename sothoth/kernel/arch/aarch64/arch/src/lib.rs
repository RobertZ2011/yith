#![no_std]
#![feature(asm)]
#![feature(const_fn)]

extern crate rlibc;
extern crate common;
extern crate spin;

mod panic;
mod isr;
mod vga_console;
mod idt;
mod cpuid;
mod apic;

pub use isr::isr_handler;

use spin::Mutex;
use common::console::Console;
use core::fmt::Arguments;
use core::fmt::Write;

const KERNEL_CS: u16 = 0x18;
const KERNEL_DS: u16 = 0x20;

pub fn panic_fmt(fmt: Arguments, file: &'static str, line: u32) -> ! {
    unsafe { panic::panic_fmt(fmt, file, line) }
}

pub fn init() {
    let console = get_console();

    console.lock().print("Setting up IDT\n");
    idt::init();
}

pub fn is_supported() -> bool {
    true
}

pub fn get_console() -> &'static Mutex<Console> {
    &vga_console::CONSOLE
}

pub fn enable_interrupts() {
    unsafe { asm!("sti" :::: "volatile"); }
}

pub fn disable_interrupts() {
    unsafe { asm!("cli" :::: "volatile"); }
}

pub fn halt() {
    unsafe { asm!("hlt" :::: "volatile"); }
}

pub fn debug_break() {
    unsafe { asm!("xchg %bx, %bx"); }
}
