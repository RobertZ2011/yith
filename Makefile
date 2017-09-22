ARCH ?= x86

clean:
	-rm os.iso
	-make -C shoggoth clean
	-make -C sothoth clean

bochs: iso
	-bochs -f bochsrc -q

qemu: iso
	-qemu-system-x86_64 -cdrom os.iso -m 128

iso: shoggoth/shoggoth.elf sothoth/sothoth.elf
	cp shoggoth/shoggoth.elf iso/boot/shoggoth.elf
	cp sothoth/sothoth.elf iso/boot/sothoth.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o os.iso iso

sothoth/sothoth.elf:
	make "arch=$(ARCH)" -C sothoth

shoggoth/shoggoth.elf:
	make "arch=$(ARCH)" -C shoggoth
