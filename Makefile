


build:
	i686-elf-as boot.s -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c string.c -o string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c io.c -o io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c terminal.c -o terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o myos.bin -Wall -ffreestanding -O2 -nostdlib io.o boot.o kernel.o string.o terminal.o -lgcc
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	./mkrescue.sh -o myos.iso isodir


run:
	qemu-system-i386 -cdrom myos.iso