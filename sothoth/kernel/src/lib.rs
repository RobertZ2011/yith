#![feature(lang_items)]
#![no_std]
#![feature(unwind_attributes)]

extern crate common;
extern crate arch;

mod panic;

#[no_mangle]
pub extern fn kmain() {
    let console = arch::get_console();

    console.lock().clear();
    console.lock().print("The Great Kernel of Yith\n");
    arch::init();
}

#[lang = "eh_personality"]
extern fn eh_personality() {}
