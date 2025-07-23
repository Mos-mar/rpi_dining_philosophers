#include "gpioManager.h"
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

GpioManager::GpioManager(const std::string& chip_name) : chip(chip_name) 
{}

void GpioManager::init_pin(unsigned int gpio_num, const std::string& consumer) {
    gpiod::line line = chip.get_line(gpio_num);
    line.request({consumer, gpiod::line_request::DIRECTION_OUTPUT, 0});
    gpio_register[gpio_num] = std::move(line);
    states[gpio_num] = false;
}

void GpioManager::set_high(unsigned int gpio_num) {
    gpio_register.at(gpio_num).set_value(1);
    states[gpio_num] = true;
}

void GpioManager::set_low(unsigned int gpio_num) {
    gpio_register.at(gpio_num).set_value(0);
    states[gpio_num] = false;
}

void GpioManager::toggle(unsigned int gpio_num) {
    bool current = states[gpio_num];
    gpio_register.at(gpio_num).set_value(!current);
    states[gpio_num] = !current;
    std::this_thread::sleep_for(std::chrono::seconds(1));// change this
}

void GpioManager::blink(unsigned int gpio_num, unsigned int times, unsigned int ms_delay) {
    for (unsigned int i = 0; i < times; ++i) {
        set_high(gpio_num);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms_delay));
        set_low(gpio_num);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms_delay));
    }
}
