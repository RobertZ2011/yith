ARCH ?= x86
CC := i686-elf-gcc
LD := i686-elf-gcc
CPP := i686-elf-g++
AR := i686-elf-ar
AS := i686-elf-as
CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11
LDFLAGS := $(CPPFLAGS) -g

CPPFILES := $(wildcard src/*.cpp)
ASMFILES := $(wildcard src/*.s)
CFILES := $(wildcard src/*.c)
CPPOBJS := $(CPPFILES:%.cpp=%.o)
ASMOBJS := $(ASMFILES:%.s=%.o)
COBJS := $(CFILES:%.c=%.o)

CRTBEGIN := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtbegin.o)
CRTEND := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtend.o)
CRTI := src/arch/$(ARCH)/src/crti.o
CRTN := src/arch/$(ARCH)/src/crtn.o

all: shoggoth.elf

clean:
	-make -C src/arch/$(ARCH) clean
	-rm src/*.o
	-rm *.elf

shoggoth.elf: src/arch/$(ARCH)/arch.o $(ASMOBJS) $(CPPOBJS) $(COBJS)
	$(LD) $(LDFLAGS) -T src/arch/$(ARCH)/linker.ld -o shoggoth.elf $(CRTI) $(CRTBEGIN) src/arch/$(ARCH)/arch.o $(ASMOBJS) $(CPPOBJS) $(COBJS) $(CRTEND) $(CRTN)

src/arch/$(ARCH)/arch.o:
	make -C src/arch/$(ARCH) "ARCH=$(ARCH)"

%.o: %.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS)

%.o: %.s
	$(AS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)
