#include "../../lib/com/port.h"

using namespace oudad::common;
using namespace oudad::com;


Port::Port(uint16_t portNumber) {
    this->portNumber = portNumber;
}

Port::~Port() {

}

Port8Bit::Port8Bit(uint16_t portNumber) : Port(portNumber) {
}

Port8Bit::~Port8Bit() {

}

void Port8Bit::Write(uint8_t data) {
    Write8(portNumber, data);
}

uint8_t Port8Bit::Read() {
    return Read8(portNumber);
}

Port8BitSlow::Port8BitSlow(uint16_t portNumber) : Port8Bit(portNumber) {
}

Port8BitSlow::~Port8BitSlow() {

}

void Port8BitSlow::Write(uint8_t data) {
    Write8Slow(portNumber, data);
}

Port16Bit::Port16Bit(uint16_t portNumber) : Port(portNumber) {
}

Port16Bit::~Port16Bit() {
}

void Port16Bit::Write(uint16_t data) {
    Write16(portNumber, data);
}

uint16_t Port16Bit::Read() {
    return Read16(portNumber);
}

Port32Bit::Port32Bit(uint16_t portNumber) : Port(portNumber) {
}

Port32Bit::~Port32Bit() {

}

void Port32Bit::Write(uint32_t data) {
    Write32(portNumber, data);
}

uint32_t Port32Bit::Read() {
    return Read32(portNumber);
}