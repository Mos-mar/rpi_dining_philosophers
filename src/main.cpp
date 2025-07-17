#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>


#include "gpioManager.h"





int main() {   
    GpioManager g1,g2;

    std::thread t1(
        [&g1](){
        g1.init_pin(26,"GREEN!");
        g1.blink(26,3,1000);
        
    });

    std::thread t2(
        [&g2](){
        g2.init_pin(19,"YELLOW!");
        g2.toggle(19);
    });

    t1.join();
    t2.join();  
    g2.set_low(19);

}



