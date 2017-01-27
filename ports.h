#ifndef __PORT_H
#define __PORT_H
#include "types.h"


class Port {
protected:
	uint16_t PortNumber;
	Port(uint16_t PortNumber);
	~Port();
};

class Port8Bit : public Port {
	public:
		Port8Bit(uint16_t PortNumber);
		~Port8Bit();
		virtual void Write(uint8_t data);
		virtual uint8_t Read();
};

class Port8BitSlow : public Port {
	public:
		Port8BitSlow(uint16_t PortNumber);
		~Port8BitSlow();
		virtual void Write(uint8_t data);
};

class Port16Bit : public Port {
	public:
		Port16Bit(uint16_t PortNumber);
		~Port16Bit();
		virtual void Write(uint16_t data);
		virtual uint16_t Read();
};

class Port32Bit : public Port {
	public:
		Port32Bit(uint32_t PortNumber);
		~Port32Bit();
		virtual void Write(uint32_t data);
		virtual uint32_t Read();
};

#endif