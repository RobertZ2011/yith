ARCH ?= x86

CC := x86_64-elf-gcc
LD := x86_64-elf-ld
CPP := x86_64-elf-g++
AR := x86_64-elf-ar
AS := x86_64-elf-as
CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone -Wall -Werror -O2
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11
LDFLAGS := --gc-sections

CRTBEGIN := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtbegin.o)
CRTEND := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtend.o)
CRTI := build/crti.o
CRTN := build/crtn.o

all: sothoth.elf

clean:
	-rm build/*.o
	-rm build/*.a
	-rm sothoth.elf

sothoth.elf:
	make -C kernel "ARCH=$(ARCH)"
	$(LD) $(LDFLAGS) -T kernel/arch/$(ARCH)/linker.ld -o sothoth.elf $(CRTI) $(CRTBEGIN) --start-group build/libkernel.a build/libarch.a --end-group $(CRTEND) $(CRTN)
