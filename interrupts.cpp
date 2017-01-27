#include "interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];
InterruptManager* InterruptManager::ActivateInterruptManager = 0;
void InterruptManager::SetInterruptDescriptorTableEntry(uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset, void (*handler)(), uint8_t descriptorPrivilegeLevel, uint8_t descriptorType) {
	const uint8_t IDT_DESC_PRESENT = 0x80;
	interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t) handler) & 0xFFFF;
	interruptDescriptorTable[interruptNumber].handlerAddressHighBits = (((uint32_t) handler) >> 16) & 0xFFFF;
	interruptDescriptorTable[interruptNumber].gdtCodeSegmentSelector = codeSegmentSelectorOffset;
	interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | descriptorType | ((descriptorPrivilegeLevel & 3) << 5);
	interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt) {
	uint16_t codeSegment = gdt->CodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xE;
	for(uint16_t i = 255; i > 0; --i) 
		SetInterruptDescriptorTableEntry(i, codeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);

	SetInterruptDescriptorTableEntry(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
	
	InterruptDescriptorTablePointer idtPtr;
	idtPtr.size = 256 * sizeof(GateDescriptor) - 1;
	idtPtr.base = (uint32_t) interruptDescriptorTable;
	asm volatile("lidt %0" : : "m" (idtPtr));
}

InterruptManager::~InterruptManager() {

}

void InterruptManager::Activate() {
	if(ActivateInterruptManager != 0)
		ActivateInterruptManager->Deactivate();
	ActivateInterruptManager = this;
	asm("sti");
}

void InterruptManager::Deactivate() {
	if(ActivateInterruptManager == this){
		ActivateInterruptManager = 0;
		asm("cli");
	}
}

uint32_t InterruptManager::DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp) {
	printf(" INTERRUPT");
	return esp;
}

uint32_t InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp) {
	if(ActivateInterruptManager != 0)
		return ActivateInterruptManager->DoHandleInterrupt(interruptNumber, esp);
	return esp;
}