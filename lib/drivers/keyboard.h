#ifndef __OUDAD__DRIVERS__KEYBOARD_H
#define __OUDAD__DRIVERS__KEYBOARD_H

#include "../common/types.h"
#include "../com/interrupts.h"
#include "drivers.h"
#include "../com/port.h"

namespace oudad {
    namespace drivers {
        class KeyboardEventHandler {
        public:
            KeyboardEventHandler();
            virtual void keyPress(char);
            virtual void keyRelease(char);
        };
        
        class KeyboardDriver : public oudad::com::InterruptHandler, public Driver {
            oudad::com::Port8Bit dataport;
            oudad::com::Port8Bit commandport;
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(oudad::com::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual oudad::common::uint32_t HandleInterrupt(oudad::common::uint32_t esp);
            virtual void Activate();
        };
    }
}
    
#endif