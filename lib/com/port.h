#ifndef __OUDAD__COM__PORT_H
#define __OUDAD__COM__PORT_H

#include "../common/types.h"

namespace oudad {
    namespace com {
        class Port {
            protected:
                Port(oudad::common::uint16_t portNumber);
                ~Port();
                oudad::common::uint16_t portNumber;
        };

        class Port8Bit : public Port {
            public:
                Port8Bit(oudad::common::uint16_t portNumber);
                ~Port8Bit();

                virtual oudad::common::uint8_t Read();
                virtual void Write(oudad::common::uint8_t data);

            protected:
                static inline oudad::common::uint8_t Read8(oudad::common::uint16_t _port) {
                    oudad::common::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(oudad::common::uint16_t _port, oudad::common::uint8_t _data){
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };

        class Port8BitSlow : public Port8Bit {
            public:
                Port8BitSlow(oudad::common::uint16_t portNumber);
                ~Port8BitSlow();

                virtual void Write(oudad::common::uint8_t data);
            protected:
                static inline void Write8Slow(oudad::common::uint16_t _port, oudad::common::uint8_t _data) {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }
        };

        class Port16Bit : public Port {
            public:
                Port16Bit(oudad::common::uint16_t portNumber);
                ~Port16Bit();

                virtual oudad::common::uint16_t Read();
                virtual void Write(oudad::common::uint16_t data);

            protected:
                static inline oudad::common::uint16_t Read16(oudad::common::uint16_t _port) {
                    oudad::common::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(oudad::common::uint16_t _port, oudad::common::uint16_t _data) {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port32Bit : public Port {
            public:
                Port32Bit(oudad::common::uint16_t portNumber);
                ~Port32Bit();

                virtual oudad::common::uint32_t Read();
                virtual void Write(oudad::common::uint32_t data);

            protected:
                static inline oudad::common::uint32_t Read32(oudad::common::uint16_t _port) {
                    oudad::common::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(oudad::common::uint16_t _port, oudad::common::uint32_t _data) {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };
    }
}

#endif