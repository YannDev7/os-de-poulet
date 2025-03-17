
CFLAGS := -std=gnu99 -ffreestanding -Wall -Wextra
SOURCES := kernel.o string.o io.o terminal.o memory.o


build-std:
	for file in $(SOURCES) ; do \
		i686-elf-gcc -c $${file%.*}.c -o $$file $(CFLAGS) ; \
	done
	i686-elf-ar crvs libstd.a $(SOURCES)

build: build-std
	i686-elf-gcc -T linker.ld -o myos.bin $(CFLAGS) -nostdlib libstd.a -lgcc
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	./mkrescue.sh -o myos.iso isodir


run:
	qemu-system-i386 -cdrom myos.iso