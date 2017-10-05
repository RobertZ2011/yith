use console_trait;

pub trait Arch {
    fn init(&mut self);
    fn is_supported(&self) -> bool;
    fn get_console<'a>(&'a self) -> &'a console_trait::Console;
}
