CC := x86_64-elf-gcc
LD := x86_64-elf-ld
CPP := x86_64-elf-g++
AR := x86_64-elf-ar
AS := x86_64-elf-as

CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone -Wall -Werror -O2
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11

CPPFILES := $(wildcard src/*.cpp)
ASMNAMES := start.s isr.s
ASMFILES := $(ASMNAMES:%.s=src/%.s)
CFILES := $(wildcard src/*.c)
CPPOBJS := $(CPPFILES:%.cpp=%.o)
ASMOBJS := $(ASMFILES:%.s=%.o)
COBJS := $(CFILES:%.c=%.o)

all: libarch.a crti.o crtn.o
	mv libarch.a ../../../../build
	mv crti.o ../../../../build
	mv crtn.o ../../../../build

clean:
	-rm *.o
	-rm *.a

libarch.a: $(COBJS) $(CPPOBJS) $(ASMOBJS)
	$(AR) -r -o libarch.a $(COBJS) $(CPPOBJS) $(ASMOBJS)

crti.o:
	$(AS) -o crti.o src/crti.s

crtn.o:
	$(AS) -o crtn.o src/crtn.s

%.o: %.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS)

%.o: %.s
	$(AS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)
