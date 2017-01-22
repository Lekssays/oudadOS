
void print(char* str) {
	unsigned short* VideoMemory = (unsigned short*) 0xb8000;

	for(int i = 0; str[i] != '\0'; i++)
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

extern "C" void kernelMain(void* multibootStrcuture, unsigned int magicNumber) {
	print("Hello World! -- 3ezzy loves you all!");
	while(1);
}