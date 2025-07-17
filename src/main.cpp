#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>


#include "gpioManager.h"





int main() {
    
    
    GpioManager g1,g2;
    g1.init_pin(26,"GREEN!");
    g1.blink(26,3,1000);

    g2.init_pin(19,"YELLOW!");
    g2.toggle(19);
    g2.set_low(19);
    
    
    

}



