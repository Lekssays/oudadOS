#include "../lib/common/types.h"
#include "../lib/gdt.h"
#include "../lib/com/interrupts.h"
#include "../lib/drivers/drivers.h"
#include "../lib/drivers/keyboard.h"
#include "../lib/drivers/mouse.h"

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
			/*case '0x08' : 
				x--; 
				VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
			break;*/
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

class MouseToConsole : public MouseEventHandler {
    int8_t x, y;
public:
    
    MouseToConsole() {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = 40;
        y = 12;
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);        
    }
    
    virtual void OnMouseMove(int xoffset, int yoffset) {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                            | (VideoMemory[80 * y + x] & 0xF000) >> 4
                            | (VideoMemory[80 * y + x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                            | (VideoMemory[80 * y + x] & 0xF000) >> 4
                            | (VideoMemory[80 * y + x] & 0x00FF);
    }
    
};

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
    MouseToConsole mshandler;
    MouseDriver mouse(&interrupts, &mshandler);
    drvManager.AddDriver(&mouse);
    drvManager.ActivateAll();
	interrupts.Activate();
	while(1);
} 