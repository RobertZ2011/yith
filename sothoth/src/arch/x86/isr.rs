#[repr(C)]
#[repr(packed)]
pub struct FPUState {

}

#[repr(C)]
#[repr(packed)]
pub struct ISRState<'a> {
    fpu_state: &'a FPUState,
    gs: u64,
    fs: u64,
    es: u64,
    ss: u64,
    ds: u64,
    r15: u64,
    r14: u64,
    r13: u64,
    r12: u64,
    r11: u64,
    r10: u64,
    r9: u64,
    r8: u64,
    rsi: u64,
    rdi: u64,
    rdx: u64,
    rcx: u64,
    rbx: u64,
    rax: u64,
    rbp: u64,
    rsp: u64,
    int_no: u64,
    err: u64,
    rip: u64,
    cs: u64,
    rflags: u64,
    user_rsp: u64,
    user_ss: u64
}

#[link="arch"]
extern {
    pub fn isr0();
}

#[allow(dead_code)]
#[no_mangle]
pub extern fn isr_handler(state: &ISRState) {

}
