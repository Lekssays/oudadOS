#include "../../lib/drivers/keyboard.h"

using namespace oudad::common;
using namespace oudad::drivers;
using namespace oudad::com;

KeyboardEventHandler::KeyboardEventHandler() { 

}

void KeyboardEventHandler::keyPress(char) {

}

void KeyboardEventHandler::keyRelease(char) 
{
}

KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler) : InterruptHandler(manager, 0x21), dataport(0x60), commandport(0x64) {
    this->handler = handler;
}

KeyboardDriver::~KeyboardDriver() {
}

void printf(char*);
void printfHex(uint8_t);

void KeyboardDriver::Activate() {
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    uint8_t key = dataport.Read();
    
    if(handler == 0)
        return esp;
    
    if(key < 0x80) {
        switch(key) {
            case 0x02: handler->keyPress('1'); break;
            case 0x03: handler->keyPress('2'); break;
            case 0x04: handler->keyPress('3'); break;
            case 0x05: handler->keyPress('4'); break;
            case 0x06: handler->keyPress('5'); break;
            case 0x07: handler->keyPress('6'); break;
            case 0x08: handler->keyPress('7'); break;
            case 0x09: handler->keyPress('8'); break;
            case 0x0A: handler->keyPress('9'); break;
            case 0x0B: handler->keyPress('0'); break;

            case 0x10: handler->keyPress('q'); break;
            case 0x11: handler->keyPress('w'); break;
            case 0x12: handler->keyPress('e'); break;
            case 0x13: handler->keyPress('r'); break;
            case 0x14: handler->keyPress('t'); break;
            case 0x15: handler->keyPress('z'); break;
            case 0x16: handler->keyPress('u'); break;
            case 0x17: handler->keyPress('i'); break;
            case 0x18: handler->keyPress('o'); break;
            case 0x19: handler->keyPress('p'); break;

            case 0x1E: handler->keyPress('a'); break;
            case 0x1F: handler->keyPress('s'); break;
            case 0x20: handler->keyPress('d'); break;
            case 0x21: handler->keyPress('f'); break;
            case 0x22: handler->keyPress('g'); break;
            case 0x23: handler->keyPress('h'); break;
            case 0x24: handler->keyPress('j'); break;
            case 0x25: handler->keyPress('k'); break;
            case 0x26: handler->keyPress('l'); break;

            case 0x2C: handler->keyPress('y'); break;
            case 0x2D: handler->keyPress('x'); break;
            case 0x2E: handler->keyPress('c'); break;
            case 0x2F: handler->keyPress('v'); break;
            case 0x30: handler->keyPress('b'); break;
            case 0x31: handler->keyPress('n'); break;
            case 0x32: handler->keyPress('m'); break;
            case 0x33: handler->keyPress(','); break;
            case 0x34: handler->keyPress('.'); break;
            case 0x35: handler->keyPress('-'); break;

            case 0x1C: handler->keyPress('\n'); break;
            case 0x39: handler->keyPress(' '); break;

            default: {
                printf("KEYBOARD 0x");
                printfHex(key);
                break;
            }
        }
    }
    return esp;
}