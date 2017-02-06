.set IRQ_BASE, 0x20

.section .text
.extern _ZN16InterruptManager15HandleInterruptEhj
 
.macro HandleExceptions num 
.global _ZN16InterruptManager26HandleExceptions\num\()Ev
_ZN16InterruptManager26HandleExceptions\num\()Ev:
	movb $\num, (interruptNumber)
	jmp int_bottom
.endm

.macro HandleInterruptRequest num 
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptNumber)
	pushl $0
	jmp int_bottom
.endm


HandleInterruptRequest 0x00
HandleInterruptRequest 0x01


int_bottom:
	# push into the stack
	pusha 
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	pushl %esp
	push (interruptNumber)
	call _ZN16InterruptManager15HandleInterruptEhj
	add %esp, 6
	movl %eax, %esp

	# Pop in reverse order since it is a stack 
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

.global _ZN16InterruptManager22IgnoreInterruptRequestEv
_ZN16InterruptManager22IgnoreInterruptRequestEv:
	iret
	

.data 
	interruptNumber: .byte 0