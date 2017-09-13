CC := i686-elf-gcc
LD := i686-elf-ld
CPP := i686-elf-g++
AR := i686-elf-ar
AS := i686-elf-as
CFLAGS := -ffreestanding -fno-builtin -nostdlib -mno-red-zone -Wall -Werror -O2
CPPFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++11

CPPFILES := $(wildcard src/*.cpp)
ASMFILES := src/boot.s src/isrS.s src/irqS.s
CFILES := $(wildcard src/*.c)
CPPOBJS := $(CPPFILES:%.cpp=%.o)
ASMOBJS := $(ASMFILES:%.s=%.o)
COBJS := $(CFILES:%.c=%.o)

ARCH ?= x86

all: arch.o src/crti.o src/crtn.o

clean:
	-rm src/*.o
	-rm *.o
	-rm *.a

arch.o: $(ASMOBJS) $(CPPOBJS) $(COBJS)
	$(LD) -r -o arch.o $(ASMOBJS) $(CPPOBJS) $(COBJS)

src/crti.o:
	$(AS) -o src/crti.o src/crti.s

src/crtn.o:
	$(AS) -o src/crtn.o src/crtn.s

%.o: %.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS)

%.o: %.s
	$(AS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)
