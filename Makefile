# Build OS's Files
cpp_params = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
as_params = --32
ld_params = -melf_i386
o_files = loader.o kernel.o

%.o: %.cpp
	g++ $(cpp_params) -o $@ -c $<

%.o: %.s
	as $(as_params) -o $@ $< 

oudad.bin: linker.ld $(o_files)
	ld $(ld_params) -T $< -o $@ $(o_files)

install: oudad.bin
	sudo cp $< /boot/oudad.bin