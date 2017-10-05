pub mod isr;
pub mod console;
mod idt;


use arch_trait;
use console_trait;

struct Arch {

}

impl Arch {
    fn setup_idt(&self) {
        unsafe {
            idt::init();
        }
    }
}

/*impl arch_trait::Arch for Arch {
    fn init(&mut self) {

    }

    fn is_supported(&self) -> bool {
        true
    }

    fn get_console(&'a self) -> &'a console_trait::Console {

    }
}*/
