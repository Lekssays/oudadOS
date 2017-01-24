#include "port.h"

Port::Port(uint16_t PortNumber) {
	this->PortNumber = PortNumber;
} 


Port::~Port() {

}

// 8-bit
Port8Bit::Port8Bit(uint16_t PortNumber):Port(PortNumber) { 

};


Port8Bit::~Port8Bit() {

}

void Port8Bit::Write(uint8_t data) {
	__asm__ volatile("outb %0, %1": : "a" (data), "Nd" (PortNumber));
}


uint8_t Port8Bit::Read() {
	uint8_t result;
	__asm__ volatile("inb %1, %0": "=a" (result) : "Nd" (PortNumber));
	return result;
}

// Slow 8-bit
Port8BitSlow::Port8BitSlow(uint16_t PortNumber):Port(PortNumber) { 

};


Port8BitSlow::~Port8BitSlow() {

}

void Port8BitSlow::Write(uint8_t data) {
	__asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:": : "a" (data), "Nd" (PortNumber));
}


// 16-bit

Port16Bit::~Port16Bit() {

}

Port16Bit::Port16Bit(uint16_t PortNumber):Port(PortNumber) { 

};


void Port16Bit::Write(uint16_t data) {
	__asm__ volatile("outw %0, %1": : "a" (data), "Nd" (PortNumber));
}


uint16_t Port16Bit::Read() {
	uint16_t result;
	__asm__ volatile("inw %1, %0": "=a" (result) : "Nd" (PortNumber));
	return result;
}


// 32-bit
Port32Bit::~Port32Bit() {

}


Port32Bit::Port32Bit(uint32_t PortNumber):Port(PortNumber) { 

};


void Port32Bit::Write(uint32_t data) {
	__asm__ volatile("outl %0, %1": : "a" (data), "Nd" (PortNumber));
}


uint32_t Port32Bit::Read() {
	uint32_t result;
	__asm__ volatile("inl %1, %0": "=a" (result) : "Nd" (PortNumber));
	return result;
}