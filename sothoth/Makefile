ARCH ?= x86

CC := x86_64-elf-gcc
LD := x86_64-elf-ld
CPP := x86_64-elf-g++
AR := x86_64-elf-ar
AS := x86_64-elf-as
CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone -Wall -Werror -O2
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11

CPPFILES := $(wildcard src/*.cpp)
ASMFILES :=
CFILES := $(wildcard src/*.c)
CPPOBJS := $(CPPFILES:%.cpp=%.o)
ASMOBJS := $(ASMFILES:%.s=%.o)
COBJS := $(CFILES:%.c=%.o)

CRTBEGIN := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtbegin.o)
CRTEND := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtend.o)
CRTI := src/arch/$(ARCH)/crti.o
CRTN := src/arch/$(ARCH)/crtn.o
TARGET := $(ARCH)-yith

all: sothoth.elf

clean:
	make -C build/$(ARCH) clean
	-rm *.o
	-rm *.rlib
	-rm *.a
	-rm *.elf
	-rm *.json
	-rm -r target

sothoth.elf: libarch.a $(TARGET).json
	xargo build --target=$(TARGET) --verbose
	-cp target/$(TARGET)/debug/libsothoth.a .
	-cp target/$(TARGET)/release/libsothoth.a .
	$(LD) $(LDFLAGS) -T build/$(ARCH)/linker.ld --gc-sections -o sothoth.elf $(CRTI) $(CRTBEGIN) libarch.a libsothoth.a $(ASMOBJS) $(CPPOBJS) $(COBJS) $(CRTEND) $(CRTN)

$(TARGET).json:
	ln -s build/$(ARCH)/$(TARGET).json $(TARGET).json

libarch.a:
	make "arch=$(ARCH)" -C build/$(ARCH)
	cp build/$(ARCH)/libarch.a .

%.o: %.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS)

%.o: %.s
	$(AS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)
