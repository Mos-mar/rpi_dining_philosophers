#pragma once
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include "philosopher.h"

class DinerManager {
private:
    std::vector<std::unique_ptr<Philosopher>> allPhilosophers;
    std::vector<std::shared_ptr<std::mutex>> forks;
    std::atomic<bool> stop;
    int number_of_philosophers;
    static const std::vector<int> valid_gpio_pins; // List of valid GPIO pins

public:
    DinerManager(int number_of_philosophers, 
                 int time_to_die, 
                 int time_to_eat, 
                 int time_to_sleep, 
                 int number_of_times_each_philosopher_must_eat);

    void startAll();
    void joinAll();
    void stopAll();

private:
    void initializePhilosophers(int time_to_die, 
                               int time_to_eat, 
                               int time_to_sleep, 
                               int number_of_times_each_philosopher_must_eat);
};