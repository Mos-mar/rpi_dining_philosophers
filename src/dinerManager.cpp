#include "dinerManager.h"

// Define valid GPIO pins
const std::vector<int> DinerManager::valid_gpio_pins = {22, 16, 18, 19, 26};

DinerManager::DinerManager(int number_of_philosophers, 
                           int time_to_die, 
                           int time_to_eat, 
                           int time_to_sleep, 
                           int number_of_times_each_philosopher_must_eat)
    : number_of_philosophers(number_of_philosophers), stop(false) {
    // Initialize forks
    for (int i = 0; i < number_of_philosophers; ++i) {
        forks.push_back(std::make_shared<std::mutex>());
    }
    // Initialize philosophers
    initializePhilosophers(time_to_die, time_to_eat, time_to_sleep, 
                          number_of_times_each_philosopher_must_eat);
}

void DinerManager::initializePhilosophers(int time_to_die, 
                                         int time_to_eat, 
                                         int time_to_sleep, 
                                         int number_of_times_each_philosopher_must_eat) {
    for (int i = 0; i < number_of_philosophers; ++i) {
        // Assign left and right forks (circular arrangement)
        auto left_fork = forks[i];
        auto right_fork = forks[(i + 1) % number_of_philosophers];
        // Ensure consistent ordering to prevent deadlock (e.g., lower-indexed fork first)
        if (i % 2 == 1) {
            std::swap(left_fork, right_fork);
        }
        // Create philosopher with GPIO pin (assuming GPIO pin = philosopher ID)
        allPhilosophers.push_back(std::make_unique<Philosopher>(
            "Philosopher_" + std::to_string(i), // Name
            this->valid_gpio_pins[i], // ID (GPIO pin)
            time_to_die,
            time_to_eat,
            time_to_sleep,
            number_of_times_each_philosopher_must_eat,
            stop,
            left_fork,
            right_fork
        ));
    }
}

void DinerManager::startAll() {
    for (auto& philosopher : allPhilosophers) {
        philosopher->start();
    }
}

void DinerManager::joinAll() {
    for (auto& philosopher : allPhilosophers) {
        philosopher->join();
    }
}

void DinerManager::stopAll() {
    stop = true;
}