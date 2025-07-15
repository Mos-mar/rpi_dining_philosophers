#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    constexpr auto chipname = "gpiochip0";
    constexpr unsigned int line_num = 26;

    gpiod::chip chip1(chipname);
    gpiod::line line16 = chip1.get_line(line_num); //green

    line16.request({"diningPhilosophers",gpiod::line_request::DIRECTION_OUTPUT,0});

    for(auto i = 0 ; i < 20 ; ++i)
    {
        if(i % 2 == 0)
        {
          line16.set_value(1);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        } 
        else
        {
          line16.set_value(0);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        } 
    }
 
    line16.set_value(0);


       
    return 0;
}
