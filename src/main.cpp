#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>


#include "gpioManager.h"
#include "dinerManager.h"
#include "philosopher.h"




//5 ARGUMENTS EXPECTED AT ALL TIMES
int main(int argc, char* argv) {   
    GpioManager g1,g2,g3;

    std::thread t1(
        [&g1](){
        g1.init_pin(26,"GREEN!");
        //g1.blink(26,50,85);
        g1.set_high(26);
        
    });

    std::thread t2(
        [&g2](){
        g2.init_pin(19,"YELLOW!");
        g2.set_high(19);
    });

     std::thread t3(
        [&g3](){
        g3.init_pin(16,"BLUE!");
        //g3.blink(16,50,85);
        g3.set_high(16);
        
    });

    t1.join();
    t2.join();  
    t3.join();
    g2.set_low(19);
    g1.set_low(26);
    g3.set_low(16);
}



