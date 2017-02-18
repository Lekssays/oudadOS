#ifndef __OUDAD__COM__PCI_H
#define __OUDAD__COM__PCI_H

#include "../common/types.h"
#include "port.h"
#include "interrupts.h"
#include "../drivers/drivers.h"

namespace oudad {
    namespace com {

        enum BaseAddressRegisterType {
            MemoryMapping = 0,
            InputOutput = 1
        };
        
        class BaseAddressRegister {
        public:
            bool prefetchable;
            oudad::common::uint8_t* address;
            oudad::common::uint32_t size;
            BaseAddressRegisterType type;
        };
        
        
        
        class PeripheralComponentInterconnectDeviceDescriptor {
        public:
            oudad::common::uint32_t portBase;
            oudad::common::uint32_t interrupt;
            
            oudad::common::uint16_t bus;
            oudad::common::uint16_t device;
            oudad::common::uint16_t function;

            oudad::common::uint16_t vendor_id;
            oudad::common::uint16_t device_id;
            
            oudad::common::uint8_t class_id;
            oudad::common::uint8_t subclass_id;
            oudad::common::uint8_t interface_id;

            oudad::common::uint8_t revision;
            
            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();
            
        };


        class PeripheralComponentInterconnectController {
            Port32Bit dataPort;
            Port32Bit commandPort;
            
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();
            
            oudad::common::uint32_t Read(oudad::common::uint16_t bus, oudad::common::uint16_t device, oudad::common::uint16_t function, oudad::common::uint32_t registeroffset);
            void Write(oudad::common::uint16_t bus, oudad::common::uint16_t device, oudad::common::uint16_t function, oudad::common::uint32_t registeroffset, oudad::common::uint32_t value);
            bool DeviceHasFunctions(oudad::common::uint16_t bus, oudad::common::uint16_t device);
            
            void SelectDrivers(oudad::drivers::DriverManager* driverManager, oudad::com::InterruptManager* interrupts);
            oudad::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, oudad::com::InterruptManager* interrupts);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(oudad::common::uint16_t bus, oudad::common::uint16_t device, oudad::common::uint16_t function);
            BaseAddressRegister GetBaseAddressRegister(oudad::common::uint16_t bus, oudad::common::uint16_t device, oudad::common::uint16_t function, oudad::common::uint16_t bar);
        };
    }
}
   
#endif