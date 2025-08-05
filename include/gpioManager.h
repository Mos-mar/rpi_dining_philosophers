#pragma once

#include <gpiod.hpp>
#include <unordered_map>
#include <string>

class GpioManager {
private:
    gpiod::chip chip;
    std::unordered_map<unsigned int, gpiod::line> gpio_register;
    std::unordered_map<unsigned int, bool> states; //Used for toggle() method
    
public:
    GpioManager(const std::string& chip_name = "gpiochip0");

    void init_pin(unsigned int gpio_num, const std::string& consumer);
    void set_high(unsigned int gpio_num);
    void set_low(unsigned int gpio_num);
    void toggle(unsigned int gpio_num); //on or off depending on current state
    void blink(unsigned int gpio_num, unsigned int times, unsigned int ms_delay);


};
