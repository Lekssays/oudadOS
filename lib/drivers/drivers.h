 #ifndef __OUDAD__DRIVERS__DRIVER_H
#define __OUDAD__DRIVERS__DRIVER_H

namespace oudad {
    namespace drivers {
        class Driver {
        public:
            Driver();
            ~Driver();
            
            virtual void Activate();
            virtual int Reset();
            virtual void Deactivate();
        };

        class DriverManager {
        public:
            Driver* drivers[265];
            int numDrivers;
            
        public:
            DriverManager();
            void AddDriver(Driver*);
            void ActivateAll();
        };
    }
}
    
#endif