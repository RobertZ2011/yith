use spin::Mutex;
use super::panic::exception_panic;

#[repr(C)]
#[repr(packed)]
pub struct FPUState {

}

#[repr(C)]
#[repr(packed)]
pub struct ISRState<'a> {
    pub cr4: u64,
    pub cr3: u64,
    pub cr2: u64,
    pub cr0: u64,
    pub fpu_state: &'a FPUState,
    pub gs: u64,
    pub fs: u64,
    pub es: u64,
    pub ss: u64,
    pub ds: u64,
    pub r15: u64,
    pub r14: u64,
    pub r13: u64,
    pub r12: u64,
    pub r11: u64,
    pub r10: u64,
    pub r9: u64,
    pub r8: u64,
    pub rsi: u64,
    pub rdi: u64,
    pub rdx: u64,
    pub rcx: u64,
    pub rbx: u64,
    pub rax: u64,
    pub rbp: u64,
    pub rsp: u64,
    pub int_no: u64,
    pub err: u64,
    pub rip: u64,
    pub cs: u64,
    pub rflags: u64,
    pub user_rsp: u64,
    pub user_ss: u64
}

#[link="arch"]
extern {
    pub fn isr0();
    pub fn isr1();
    pub fn isr2();
    pub fn isr3();
    pub fn isr4();
    pub fn isr5();
    pub fn isr6();
    pub fn isr7();
    pub fn isr8();
    pub fn isr9();
    pub fn isr10();
    pub fn isr11();
    pub fn isr12();
    pub fn isr13();
    pub fn isr14();
    pub fn isr15();
    pub fn isr16();
    pub fn isr17();
    pub fn isr18();
    pub fn isr19();
    pub fn isr20();
    pub fn isr21();
    pub fn isr22();
    pub fn isr23();
    pub fn isr24();
    pub fn isr25();
    pub fn isr26();
    pub fn isr27();
    pub fn isr28();
    pub fn isr29();
    pub fn isr30();
    pub fn isr31();
}

static PANIC_MUTEX: Mutex<i8> = Mutex::new(0);

#[allow(dead_code)]
#[no_mangle]
pub extern fn isr_handler(state: &ISRState) {
    if state.int_no < 32 && state.cs == super::KERNEL_CS as u64 {
        unsafe { exception_panic(state); }
    }
}
