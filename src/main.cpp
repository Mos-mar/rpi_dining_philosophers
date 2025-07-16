#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>

constexpr auto chipname = "gpiochip0";
constexpr unsigned int line_num = 26;

void gpioLed(const std::string& requestName, gpiod::chip& c, gpiod::line& l) {
    l.request({requestName, gpiod::line_request::DIRECTION_OUTPUT, 0});

    for (int i = 0; i < 20; ++i) {
        l.set_value(i % 2);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    l.set_value(0);
}

int main() {
    gpiod::chip chip(chipname);
    gpiod::line l1 = chip.get_line(22);
    gpiod::line l2 = chip.get_line(16);
    gpiod::line l3 = chip.get_line(18);
    gpiod::line l4 = chip.get_line(19);
    gpiod::line l5 = chip.get_line(26);

    std::thread t1(gpioLed, "led_request1", std::ref(chip), std::ref(l1));
    std::thread t2(gpioLed, "led_request2", std::ref(chip), std::ref(l2));
    std::thread t3(gpioLed, "led_request3", std::ref(chip), std::ref(l3));
    std::thread t4(gpioLed, "led_request4", std::ref(chip), std::ref(l4));
    std::thread t5(gpioLed, "led_request5", std::ref(chip), std::ref(l5));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}



