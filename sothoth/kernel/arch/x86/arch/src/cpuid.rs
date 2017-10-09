use core::ops::BitAnd;
use core::ops::BitOr;
use core::cmp::Ord;
use core::cmp::Eq;

#[repr(u64)]
#[derive(Ord)]
#[derive(Eq)]
#[derive(PartialEq)]
#[derive(PartialOrd)]
enum BasicFlag {
    FPU = 0x1,
    VME = 0x2,
    DE  = 0x4,
    PSE = 0x8,
    TSC = 0x10,
    MSR = 0x20,
    PAE = 0x40,
    MCE = 0x80,
    CX8 = 0x100,
    APIC = 0x200,

    SEP = 0x800,
    MTRR = 0x1000,
    PGE = 0x2000,
    MCA = 0x4000,
    CMOV = 0x8000,
    PAT = 0x10000,
    PSE36 = 0x20000,
    PSN = 0x40000,
    CLFSH = 0x80000,

    DS = 0x200000,
    ACPI = 0x400000,
    MMX = 0x800000,
    FXSR = 0x1000000,
    SSE = 0x2000000,
    SSE2 = 0x4000000,
    SS = 0x8000000,
    HTT = 0x10000000,
    TM = 0x20000000,
    PBE = 0x80000000,

    SSE3 = 0x1 << 32,
    PCLMULQDQ = 0x2 << 32,
    DTES64 = 0x4 << 32,
    MONITOR = 0x8 << 32,
    DSCPL = 0x10 << 32,
    VMX = 0x20 << 32,
    SMX = 0x40 << 32,
    EIST = 0x80 << 32,
    TM2 = 0x100 << 32,
    SSSE3 = 0x200 << 32,
    CNXTID = 0x400 << 32,
    SDBG = 0x800 << 32,
    FMA = 0x1000 << 32,
    CMPXCHG16B = 0x2000 << 32,
    XTPRU = 0x4000 << 32,
    PDCM = 0x8000 << 32,

    PCID = 0x20000 << 32,
    DCA = 0x40000 << 32,
    SSE41 = 0x80000 << 32,
    SSE42 = 0x100000 << 32,
    X2APIC = 0x200000 << 32,
    MOVBE = 0x400000 << 32,
    POPCNT = 0x800000 << 32,
    TSCD = 0x1000000 << 32,
    AESNI = 0x2000000 << 32,
    XSAVE = 0x4000000 << 32,
    OSXSAVE = 0x8000000 << 32,
    AVX = 0x10000000 << 32,
    F16C = 0x20000000 << 32,
    RDRAND = 0x40000000 << 32
}

#[repr(u64)]
enum ExtendedFlag {
    FPU = 0x1,
    VME = 0x2,
    DE = 0x4,
    PSE = 0x8,
    TSC = 0x10,
    MSR = 0x20,
    PAE = 0x40,
    MCE = 0x80,
    CX8 = 0x100,
    APIC = 0x200,

    SYSCALL = 0x800,
    MTRR = 0x1000,
    PGE = 0x2000,
    MCA = 0x4000,
    CMOV = 0x8000,
    PAT = 0x10000,
    PSE36 = 0x20000,

    MP = 0x80000,
    NX = 0x100000,

    MMXEXT = 0x400000,
    MMX = 0x800000,
    FXSR = 0x1000000,
    FXSROPT = 0x2000000,
    PDPE1GB = 0x4000000,
    RDTSCP = 0x8000000,

    LM = 0x20000000,
    THRDNOWEXT = 0x40000000,
    THRDNOW = 0x80000000,

    LAHFLM = 0x1 << 32,
    CMPLEGACY = 0x2 << 32,
    SVM = 0x4 << 32,
    EXTAPIC = 0x8 << 32,
    CR8LEGACY = 0x10 << 32,
    ABM = 0x20 << 32,
    SSE4A = 0x40 << 32,
    MISALIGNSSE = 0x80 << 32,
    THRNOWPRETECH = 0x100 << 32,
    OSVW = 0x200 << 32,
    IBS = 0x400 << 32,
    XOP = 0x800 << 32,
    SKINIT = 0x1000 << 32,
    WDIT = 0x2000 << 32,

    LWP = 0x8000 << 32,
    FMA4 = 0x10000 << 32,
    TCE  = 0x20000 << 32,

    NODEIDMSR = 0x80000 << 32,

    TBM = 0x200000 << 32,
    TOPOEXT = 0x400000 << 32,
    PERCTRCORE = 0x800000 << 32,
    PERCTRNB = 0x1000000 << 32,

    DBX = 0x4000000 << 32,
    PERTSC = 0x8000000 << 32,
    PCXL2I = 0x10000000  << 32
}

#[repr(u32)]
enum BasicFunction {
    HighestBasic = 0x0,
    Info = 0x1,
    Cache = 0x2,
    Serial = 0x3,
}

struct BasicFeatures(u64);
struct ExtendedFeatures(u64);

#[repr(u32)]
enum ExtendedFunction {
    HighestExtended = 0x80000000,
    Info = 0x80000001,
    Brand1 = 0x80000002,
    Brand2 = 0x80000003,
    Brand3 = 0x80000004,
    Reserved = 0x80000005,
    CacheInfo = 0x80000006,
    InvariantTSC = 0x80000007,
    AddressSize = 0x80000008
}

impl BitAnd for BasicFeatures {
    type Output = BasicFeatures;

    fn bitand(self, other: BasicFlag) -> Output {

    }
}

pub fn read_msr() -> u64 {
    0
}

pub fn write_msr() {

}

fn cpuid(function: u32) -> (u32, u32, u32, u32) {
    let mut eax = 0;
    let mut ebx = 0;
    let mut ecx = 0;
    let mut edx = 0;

    unsafe {
        asm!(
            "cpuid"
            : "={eax}"(eax), "={ebx}"(ebx), "={ecx}"(ecx), "={edx}"(edx)
            : "{eax}"(function)
            :
            : "volatile"
        )
    }

    return (eax, ebx, ecx, edx)
}

/*pub fn get_highest_basic() -> BasicFunction {
    let (eax, _, _, _) = cpuid(BasicFunction::HighestBasic as u32);
    return eax as BasicFunction;
}

pub fn get_highest_extended() -> ExtendedFunction {
    let (eax, _, _, _) = cpuid(ExtendedFunction::HighestExtended as u32);
    return eax as ExtendedFunction;
}*/

pub fn get_basic_features() -> BasicFeatures {
    let (_, _, ecx, edx) = cpuid(BasicFunction::Info as u32);
    let rcx = ecx as u64;
    let rdx = edx as u64;
    return BasicFeatures(rdx | rcx << 32);
}

pub fn get_extended_features() -> ExtendedFeatures {
    let (_, _, ecx, edx) = cpuid(ExtendedFunction::Info as u32);
    let rcx = ecx as u64;
    let rdx = edx as u64;
    return ExtendedFeatures(rdx | rcx << 32)
}
