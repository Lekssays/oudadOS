#ifndef __OUDAD__DRIVERS__MOUSE_H
#define __OUDAD__DRIVERS__MOUSE_H

#include "../common/types.h"
#include "../com/interrupts.h"
#include "drivers.h"
#include "../com/port.h"

namespace oudad {
    namespace drivers {

        class MouseEventHandler {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(oudad::common::uint8_t button);
            virtual void OnMouseUp(oudad::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public oudad::com::InterruptHandler, public Driver {
            oudad::com::Port8Bit dataport;
            oudad::com::Port8Bit commandport;
            oudad::common::uint8_t buffer[3];
            oudad::common::uint8_t offset;
            oudad::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(oudad::com::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual oudad::common::uint32_t HandleInterrupt(oudad::common::uint32_t esp);
            virtual void Activate();
        };
    }
}
    
#endif