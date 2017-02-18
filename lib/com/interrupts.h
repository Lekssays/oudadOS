#ifndef __OUDAD__COM__INTERRUPTMANAGER_H
#define __OUDAD__COM__INTERRUPTMANAGER_H

#include "../gdt.h"
#include "../common/types.h"
#include "port.h"

namespace oudad {
    namespace com {
        class InterruptManager;

        class InterruptHandler {
        protected:
            oudad::common::uint8_t InterruptNumber;
            InterruptManager* interruptManager;
            InterruptHandler(InterruptManager* interruptManager, oudad::common::uint8_t InterruptNumber);
            ~InterruptHandler();
        public:
            virtual oudad::common::uint32_t HandleInterrupt(oudad::common::uint32_t esp);
        };


        class InterruptManager {
            friend class InterruptHandler;
            protected:

                static InterruptManager* ActiveInterruptManager;
                InterruptHandler* handlers[256];

                struct GateDescriptor {
                    oudad::common::uint16_t handlerAddressLowBits;
                    oudad::common::uint16_t gdt_codeSegmentSelector;
                    oudad::common::uint8_t reserved;
                    oudad::common::uint8_t access;
                    oudad::common::uint16_t handlerAddressHighBits;
                } __attribute__((packed));

                static GateDescriptor interruptDescriptorTable[256];

                struct InterruptDescriptorTablePointer {
                    oudad::common::uint16_t size;
                    oudad::common::uint32_t base;
                } __attribute__((packed));

                oudad::common::uint16_t hardwareInterruptOffset;
                static void SetInterruptDescriptorTableEntry(oudad::common::uint8_t interrupt,
                    oudad::common::uint16_t codeSegmentSelectorOffset, 
                    void (*handler)(),
                    oudad::common::uint8_t DescriptorPrivilegeLevel, 
                    oudad::common::uint8_t DescriptorType);

                static void InterruptIgnore();

                static void HandleInterruptRequest0x00();
                static void HandleInterruptRequest0x01();
                static void HandleInterruptRequest0x02();
                static void HandleInterruptRequest0x03();
                static void HandleInterruptRequest0x04();
                static void HandleInterruptRequest0x05();
                static void HandleInterruptRequest0x06();
                static void HandleInterruptRequest0x07();
                static void HandleInterruptRequest0x08();
                static void HandleInterruptRequest0x09();
                static void HandleInterruptRequest0x0A();
                static void HandleInterruptRequest0x0B();
                static void HandleInterruptRequest0x0C();
                static void HandleInterruptRequest0x0D();
                static void HandleInterruptRequest0x0E();
                static void HandleInterruptRequest0x0F();
                static void HandleInterruptRequest0x31();

                static void HandleInterruptRequest0x80();

                static void HandleException0x00();
                static void HandleException0x01();
                static void HandleException0x02();
                static void HandleException0x03();
                static void HandleException0x04();
                static void HandleException0x05();
                static void HandleException0x06();
                static void HandleException0x07();
                static void HandleException0x08();
                static void HandleException0x09();
                static void HandleException0x0A();
                static void HandleException0x0B();
                static void HandleException0x0C();
                static void HandleException0x0D();
                static void HandleException0x0E();
                static void HandleException0x0F();
                static void HandleException0x10();
                static void HandleException0x11();
                static void HandleException0x12();
                static void HandleException0x13();
                
                Port8BitSlow picMasterCommandPort;
                Port8BitSlow picMasterDataPort;
                Port8BitSlow picSlaveCommandPort;
                Port8BitSlow picSlaveDataPort;

                static oudad::common::uint32_t HandleInterrupt(oudad::common::uint8_t interrupt, oudad::common::uint32_t esp);
                oudad::common::uint32_t DoHandleInterrupt(oudad::common::uint8_t interrupt, oudad::common::uint32_t esp);

            public:
                InterruptManager(oudad::common::uint16_t hardwareInterruptOffset, oudad::GlobalDescriptorTable* globalDescriptorTable);
                ~InterruptManager();
                oudad::common::uint16_t HardwareInterruptOffset();
                void Activate();
                void Deactivate();
        };
        
    }
}

#endif