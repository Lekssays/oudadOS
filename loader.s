.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern .kernelMain
.global loader

loader:
	mov $kernelStack, %esp
	push %eax 
	push %ebx
	call kernelMain

_stop:
	cli
	hlt
	jmp _stop

.section .bss
.space 3 * 1024 * 1024;
kernelStack: 