#include "../lib/common/types.h"
#include "../lib/gdt.h"
#include "../lib/com/interrupts.h"
#include "../lib/drivers/drivers.h"
#include "../lib/drivers/keyboard.h"

using namespace oudad;
using namespace oudad::common;
using namespace oudad::drivers;
using namespace oudad::com;

void printf(char* str) {
	static uint16_t* VideoMemory = (uint16_t*) 0xb8000;
	static uint8_t x = 0, y = 0;

	for(int i = 0; str[i] != '\0'; i++) {
		switch(str[i]) {
			case '\n': y++; x = 0; break;
			default:
				VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
				x++;	
				break;			
		} 
		if(x >= 80) {
			y++;
			x = 0;
		}
		if(y >= 25) {
			for(y = 0; y < 25; y++)
				for(x = 0; x < 80; x++)
					VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
			x = 0;
			y = 0;
		}
	}
}

void printfHex(uint8_t key) {
    char* print = "00";
    char* hex = "0123456789ABCDEF";
    print[0] = hex[(key >> 4) & 0xF];
    print[1] = hex[key & 0xF];
    printf(print);
}

void printfHex16(uint16_t key) {
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}

void printfHex32(uint32_t key) {
    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler{
public:
    void keyPress(char c) {
        char* print = " ";
        print[0] = c;
        printf(print);
    }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){
	for(constructor* i = &start_ctors; i != &end_ctors; i++) {
		(*i)();
	}
}

extern "C" void kernelMain(const void* multibootStrcuture, uint32_t magicNumber) {
	printf("oudadOS - An Open-Source Lightweight Operating System\nhttps://www.github.com/Lekssays/oudadOS\n");
	GlobalDescriptorTable gdt;
	InterruptManager interrupts(0x20, &gdt);
	DriverManager drvManager;
    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&interrupts, &kbhandler);
    drvManager.AddDriver(&keyboard);   
    drvManager.ActivateAll();
	interrupts.Activate();
	while(1);
} 