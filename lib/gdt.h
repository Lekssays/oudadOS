#ifndef __OUDAD__GDT_H
#define __OUDAD__GDT_H

#include "common/types.h"

namespace oudad {
    class GlobalDescriptorTable {
        public:
            class SegmentDescriptor {
                private:
                    oudad::common::uint16_t limit_lo;
                    oudad::common::uint16_t base_lo;
                    oudad::common::uint8_t base_hi;
                    oudad::common::uint8_t type;
                    oudad::common::uint8_t limit_hi;
                    oudad::common::uint8_t base_vhi;
                public:
                    SegmentDescriptor(oudad::common::uint32_t base, oudad::common::uint32_t limit, oudad::common::uint8_t type);
                    oudad::common::uint32_t Base();
                    oudad::common::uint32_t Limit();
            } __attribute__((packed));
        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;
        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();
            oudad::common::uint16_t CodeSegmentSelector();
            oudad::common::uint16_t DataSegmentSelector();
    };
}
    
#endif