ARCH ?= x86

CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone -Wall -Werror -O2
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11
LDFLAGS := --gc-sections

CRTBEGIN := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtbegin.o)
CRTEND := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtend.o)
CRTI := build/crti.o
CRTN := build/crtn.o

all: $(ARCH) sothoth.elf

.PHONY: build

clean:
	-rm sothoth.elf
	-rm -r build/*
	-rmdir build

build:
	mkdir build

x86:
	$(eval CC := x86_64-elf-gcc)
	$(eval LD := x86_64-elf-ld)
	$(eval CPP := x86_64-elf-g++)
	$(eval AR := x86_64-elf-ar)
	$(eval AS := x86_64-elf-as)

sothoth.elf: build
	make -C kernel "ARCH=$(ARCH)"
	$(LD) $(LDFLAGS) -T kernel/arch/$(ARCH)/linker.ld -o sothoth.elf $(CRTI) $(CRTBEGIN) --start-group build/libkernel.a build/libarch.a --end-group $(CRTEND) $(CRTN)
