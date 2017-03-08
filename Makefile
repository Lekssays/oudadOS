# Makefile to Generate an ISO Image of oudadOS
# Build OS's Files
cpp_params = -O0 -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
as_params = --32
ld_params = -melf_i386

o_files = obj/loader.o \
          obj/gdt.o \
          obj/drivers/driver.o \
          obj/com/port.o \
          obj/com/interruptstubs.o \
          obj/com/interrupts.o \
          obj/multitasking.o \
          obj/com/pci.o \
          obj/drivers/keyboard.o \
          obj/drivers/mouse.o \
          obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(cpp_params) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(as_params) -o $@ $<
	
oudadOS.bin: linker.ld $(o_files)
	ld $(ld_params) -T $< -o $@ $(o_files)
	
.PHONY: clean
clean:
	rm -f $(o_files) oudadOS.iso oudadOS.bin 
