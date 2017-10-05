use super::isr::*;

#[repr(C)]
#[repr(packed)]
#[derive(Clone, Copy, Debug)]
struct IdtEntry {
    offset_low_low: u16,
    segment: u16,
    ist: u8,
    attributes: u8,
    offset_low_high: u16,
    offset_high: u32,
    reserved: u32
}

#[repr(C)]
#[repr(packed)]
struct IdtPtr {
    limit: u16,
    addr: u64
}

#[repr(C)]
#[repr(packed)]
pub struct Idt {
    entries: [IdtEntry; 256]
}

static mut IDT : Idt = Idt {
    entries: [IdtEntry {
        offset_low_low: 0,
        segment: 0,
        ist: 0,
        attributes: 0,
        offset_low_high: 0,
        offset_high: 0,
        reserved: 0
    }; 256]
};

pub fn init() {
    unsafe {
        IDT.init();
    }
}

impl Idt {
    pub fn init(&mut self) {
        self.set_handler(0, 0x16, 0, isr0);

        self.load_idt();
    }

    fn set_handler(&mut self, index: usize, segment: u16, entry_type: u8, handler: unsafe extern fn() -> ()) {
        let addr = handler as u64;

        self.entries[index].offset_low_low = (addr & 0xFFFF) as u16;
        self.entries[index].offset_low_high = ((addr & 0xFFFF0000) >> 16) as u16;
        self.entries[index].offset_high = (addr >> 32) as u32;

        self.entries[index].segment = segment;
        self.entries[index].reserved = 0;
    }

    fn load_idt(&self) {
        let ptr = IdtPtr {
            limit: 16 * 256,
            addr: (&self.entries[0] as *const IdtEntry) as u64
        };

        unsafe {
            asm!("lidt (%rax)"
            :
            : "{rax}"(&ptr)
            :
            : "volatile");
        }
    }
}
