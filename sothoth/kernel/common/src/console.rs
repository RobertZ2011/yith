use core::fmt::Write;

#[allow(dead_code)]
#[repr(u8)]
#[derive(Debug, Clone, Copy)]
pub enum Color {
    Black = 0x0,
    Blue  = 0x1,
    Green = 0x2,
    Cyan  = 0x3,
    Red   = 0x4,
    Magenta = 0x5,
    Brown = 0x6,
    LightGray = 0x7,
    DarkGray = 0x8,
    LightBlue = 0x9,
    LightGreen = 0xA,
    LightCyan = 0xB,
    LightRed = 0xC,
    Pink = 0xD,
    Yellow = 0xE,
    White = 0xF
}

pub trait Console: Write {
    fn set_foreground(&mut self, fg: Color);
    fn set_background(&mut self, bg: Color);
    fn clear(&mut self);
    fn print(&mut self, s: &str);
}
