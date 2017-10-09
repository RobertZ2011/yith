use core::fmt::Arguments;
use arch;

#[lang = "panic_fmt"]
#[unwind]
#[no_mangle]
extern fn panic_fmt(fmt: Arguments, file: &'static str, line: u32) -> ! {
    arch::panic_fmt(fmt, file, line);
}
