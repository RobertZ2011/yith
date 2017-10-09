use core::fmt::*;
use spin::Mutex;
use common::mutex::force_acquire;
use common::console::Color;
use super::isr::ISRState;

static PANIC_LOCK: Mutex<u8> = Mutex::new(0);

pub unsafe fn panic_fmt(fmt: Arguments, file: &'static str, line: u32) -> ! {
    let panic_lock = PANIC_LOCK.lock(); //if we're already in a panic, this will be locked and we'll stop
    let mut console_lock = force_acquire(super::get_console());

    console_lock.set_foreground(Color::White);
    console_lock.set_background(Color::Red);

    console_lock.clear();
    console_lock.print("Kernel panic: ");
    console_lock.write_fmt(fmt);
    write!(console_lock, " at file: {}, line: {}", file, line);

    loop {
        super::halt();
    }
}

static EXCEPTION_MSG : [&str; 21] = [
    "Divide Error",
    "Debug Exception",
    "NMI",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprecessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Reserved",
    "x87 FPU Floating-Point Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception"
];

pub unsafe fn exception_panic(state: &ISRState) -> ! {
    let panic_lock = PANIC_LOCK.lock();
    let mut console_lock = force_acquire(super::get_console());

    console_lock.set_foreground(Color::White);
    console_lock.set_background(Color::Red);
    console_lock.clear();

    write!(console_lock, "Kernel panic: {}\n", EXCEPTION_MSG[state.int_no as usize]);

    write!(console_lock, "RAX {:08X} RBX {:08X} RCX {:08X} RDX {:08X} RSI {:08X} RDI {:08X}\n",
        state.rax >> 32,
        state.rbx >> 32,
        state.rcx >> 32,
        state.rdx >> 32,
        state.rsi >> 32,
        state.rdi >> 32
    );
    write!(console_lock, "    {:08X}     {:08X}     {:08X}     {:08X}     {:08X}     {:08X}\n\n",
        state.rax & 0xFFFFFFFF,
        state.rbx & 0xFFFFFFFF,
        state.rcx & 0xFFFFFFFF,
        state.rdx & 0xFFFFFFFF,
        state.rsi & 0xFFFFFFFF,
        state.rdi & 0xFFFFFFFF
    );


    write!(console_lock, "R8  {:08X} R9  {:08X} R10 {:08X} R11 {:08X} R12 {:08X} R13 {:08X}\n",
        state.r8 >> 32,
        state.r9 >> 32,
        state.r10 >> 32,
        state.r11 >> 32,
        state.r12 >> 32,
        state.r13 >> 32
    );
    write!(console_lock, "    {:08X}     {:08X}     {:08X}     {:08X}     {:08X}     {:08X}\n\n",
        state.r8 & 0xFFFFFFFF,
        state.r9 & 0xFFFFFFFF,
        state.r10 & 0xFFFFFFFF,
        state.r11 & 0xFFFFFFFF,
        state.r12 & 0xFFFFFFFF,
        state.r13 & 0xFFFFFFFF
    );

    write!(console_lock, "R14 {:08X} R15 {:08X} RSP {:08X} RBP {:08X} RIP {:08X}\n",
        state.r14 >> 32,
        state.r15 >> 32,
        state.rsp >> 32,
        state.rbp >> 32,
        state.rip >> 32
    );
    write!(console_lock, "    {:08X}     {:08X}     {:08X}     {:08X}     {:08X}\n\n",
        state.r14 & 0xFFFFFFFF,
        state.r15 & 0xFFFFFFFF,
        state.rsp & 0xFFFFFFFF,
        state.rbp & 0xFFFFFFFF,
        state.rip & 0xFFFFFFFF
    );

    write!(console_lock, "CR0 {:08X} CR2 {:08X} CR3 {:08X} CR4 {:08X}\n",
        state.cr0 >> 32,
        state.cr2 >> 32,
        state.cr3 >> 32,
        state.cr4 >> 32
    );
    write!(console_lock, "    {:08X}     {:08X}     {:08X}     {:08X}\n\n",
        state.cr0 & 0xFFFFFFFF,
        state.cr2 & 0xFFFFFFFF,
        state.cr3 & 0xFFFFFFFF,
        state.cr4 & 0xFFFFFFFF
    );

    write!(console_lock, "CS {:04X} DS {:04X} SS {:04X} ES {:04X} FS {:04X} GS {:04X}\n\n",
        state.cs,
        state.ds,
        state.ss,
        state.es,
        state.fs,
        state.gs
    );

    write!(console_lock, "RFLAGS {:016X}", state.rflags);

    loop {
        super::halt();
    }
}
