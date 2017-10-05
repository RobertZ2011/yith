use console_trait;
use console_trait::Color;
use core::ptr::write_volatile;
use rlibc::memset;

pub struct Console {
    x: i8,
    y: i8,
    fg: Color,
    bg: Color
}

impl Console {
    pub fn new() -> Console {
        Console {
            x: 0,
            y: 0,
            bg: Color::Black,
            fg: Color::LightGray
        }
    }
}

impl console_trait::Console for Console {
    fn set_foreground(&mut self, fg: Color) {
        self.fg = fg;
    }

    fn set_background(&mut self, bg: Color) {
        self.bg = bg;
    }

    fn clear(&mut self) {
        let fg = self.fg as u32;
        let bg = self.bg as u32;
        let color = (fg | bg << 4) << 8;

        self.x = 0;
        self.y = 0;

        unsafe {
            memset(0xB8000 as *mut u8, ((color | 0x20) << 16) as i32, 80 * 25 * 2);
        }
    }

    fn print(&mut self, s: &str) {
        let ptr = 0xB8000 as *mut u16;
        let fg = self.fg as u16;
        let bg = self.bg as u16;
        let color = (fg | bg << 4) << 8;

        for cs in s.as_bytes() {
            let c = *cs as u8;
            let cl = *cs as u16;

            if c == b'\n' {
                self.x = 0;
                self.y += 1;
                if self.y + 1 >= 80 {
                    self.y = 0;
                }
            }
            else
            if c == b'\t' {

            }

            unsafe {
                write_volatile(ptr.offset((self.x + self.y * 80) as isize), color | cl);
            }

            self.x += 1;
        }
    }
}
