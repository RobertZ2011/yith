CC := x86_64-elf-gcc
LD := x86_64-elf-ld
CPP := x86_64-elf-g++
AR := x86_64-elf-ar
AS := x86_64-elf-as
CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone -Wall -Werror -O2
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11

CPPFILES := $(wildcard ../../src/arch/x86/*.cpp)
ASMNAMES := start.s isr.s
ASMFILES := $(ASMNAMES:%.s=../../src/arch/x86/%.s)
CFILES := $(wildcard ../../src/arch/x86/*.c)
CPPOBJS := $(CPPFILES:%.cpp=%.o)
ASMOBJS := $(ASMFILES:%.s=%.o)
COBJS := $(CFILES:%.c=%.o)

all: libarch.a ../../src/x86/crti.o ../../src/x86/crtn.o

clean:
	-rm *.a
	-rm ../../src/arch/x86/*.o
	-rm ../../libarch.a

libarch.a: $(ASMOBJS) $(COBJS) $(CPPOBJS)
	ld -r -o libarch.a $(ASMOBJS) $(COBJS) $(CPPOBJS)

../../src/x86/crti.o:
	$(AS) -o ../../src/arch/x86/crti.o ../../src/arch/x86/crti.s

../../src/x86/crtn.o:
	$(AS) -o ../../src/arch/x86/crtn.o ../../src/arch/x86/crtn.s

%.o: %.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS)

%.o: %.s
	$(AS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)
