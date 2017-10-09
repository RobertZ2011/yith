use super::isr::*;
use spin::Mutex;

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
struct Idt {
    entries: [IdtEntry; 256]
}

static IDT : Mutex<Idt> = Mutex::new(Idt {
    entries: [IdtEntry {
        offset_low_low: 0,
        segment: 0,
        ist: 0,
        attributes: 0,
        offset_low_high: 0,
        offset_high: 0,
        reserved: 0
    }; 256]
});

pub fn init() {
    IDT.lock().init();
}

impl Idt {
    pub fn init(&mut self) {
        let cs = super::KERNEL_CS;
        let attr : u8 = 0x8E;

        self.set_handler(0, cs, attr, isr0);
        self.set_handler(1, cs, attr, isr1);
        self.set_handler(2, cs, attr, isr2);
        self.set_handler(3, cs, attr, isr3);
        self.set_handler(4, cs, attr, isr4);
        self.set_handler(5, cs, attr, isr5);
        self.set_handler(6, cs, attr, isr6);
        self.set_handler(7, cs, attr, isr7);
        self.set_handler(8, cs, attr, isr8);
        self.set_handler(9, cs, attr, isr9);
        self.set_handler(10, cs, attr, isr10);
        self.set_handler(11, cs, attr, isr11);
        self.set_handler(12, cs, attr, isr12);
        self.set_handler(13, cs, attr, isr13);
        self.set_handler(14, cs, attr, isr14);
        self.set_handler(15, cs, attr, isr15);
        self.set_handler(16, cs, attr, isr16);
        self.set_handler(17, cs, attr, isr17);
        self.set_handler(18, cs, attr, isr18);
        self.set_handler(19, cs, attr, isr19);
        self.set_handler(20, cs, attr, isr20);
        self.set_handler(21, cs, attr, isr21);
        self.set_handler(22, cs, attr, isr22);
        self.set_handler(23, cs, attr, isr23);
        self.set_handler(24, cs, attr, isr24);
        self.set_handler(25, cs, attr, isr25);
        self.set_handler(26, cs, attr, isr26);
        self.set_handler(27, cs, attr, isr27);
        self.set_handler(28, cs, attr, isr28);
        self.set_handler(29, cs, attr, isr29);
        self.set_handler(30, cs, attr, isr30);
        self.set_handler(31, cs, attr, isr31);

        self.load_idt();
    }

    fn set_handler(&mut self, index: usize, segment: u16, attr: u8, handler: unsafe extern fn() -> ()) {
        let addr = handler as u64;

        self.entries[index].offset_low_low = (addr & 0xFFFF) as u16;
        self.entries[index].offset_low_high = ((addr & 0xFFFF0000) >> 16) as u16;
        self.entries[index].offset_high = (addr >> 32) as u32;

        self.entries[index].segment = segment;
        self.entries[index].reserved = 0;
        self.entries[index].attributes = attr;
        self.entries[index].ist = 0;
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
