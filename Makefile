ARCH ?= x86

clean:
	-rm os.iso
	-make -C shoggoth clean
	-make -C sothoth clean

bochs: iso
	-bochs -f bochsrc -q

qemu: iso

iso: shoggoth/shoggoth.elf
	cp shoggoth/shoggoth.elf iso/boot/shoggoth.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o os.iso iso

shoggoth/shoggoth.elf:
	make "arch=$(ARCH)" -C shoggoth
