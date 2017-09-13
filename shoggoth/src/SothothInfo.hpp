#ifndef SOTHOTH_INFO
#define SOTHOTH_INFO

#include "arch/x86/src/x86.hpp"

struct SothothInfo {
    void *main;
    x86::Info *info;
};

#endif
