#include "philosopher.h"
#include <iostream>
#include <chrono>

Philosopher::Philosopher(const std::string& name,
                         int id,
                         int time_to_die, 
                         int time_to_eat,
                         int time_to_sleep,
                         int number_of_times_each_philosopher_must_eat,
                         std::atomic<bool>& stop,
                         std::shared_ptr<std::mutex> left, 
                         std::shared_ptr<std::mutex> right)
    : name(name), id(id), time_to_die(time_to_die), time_to_eat(time_to_eat),
      time_to_sleep(time_to_sleep), number_of_times_each_philosopher_must_eat(number_of_times_each_philosopher_must_eat),
      stop(stop), left(left), right(right) {
    gpio = std::make_unique<GpioManager>();
    gpio->init_pin(id, name);
    gpio->set_low(id); // Ensure LED is off initially
}

void Philosopher::think() {
    std::cout << name << " is thinking\n";
    gpio->set_high(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(this->time_to_sleep));
}

void Philosopher::eat() {
    std::cout << name << " is trying to eat\n";
    std::scoped_lock lock(*left, *right);
    std::cout << name << " is eating\n";
    gpio->blink(id, this->number_of_times_each_philosopher_must_eat, this->time_to_eat); 
}

void Philosopher::sleep() {
    std::cout << name << " is sleeping\n";
    gpio->set_low(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(this->time_to_sleep));
}

void Philosopher::start() {
    thread = std::thread(&Philosopher::run, this);
}

void Philosopher::run() {
    int meals_eaten = 0;
    auto last_meal_time = std::chrono::steady_clock::now();
    while (!stop && (this->number_of_times_each_philosopher_must_eat == -1 || meals_eaten < this->number_of_times_each_philosopher_must_eat)) {
        think();
        eat();
        meals_eaten++;
        auto now = std::chrono::steady_clock::now();
        last_meal_time = now; // Update meal time
        // Check for starvation
        if (this->time_to_die > 0 && 
            std::chrono::duration_cast<std::chrono::milliseconds>(now - last_meal_time).count() >= this->time_to_die) {
            std::cout << name << " has died\n";
            stop = true; // Stop simulation
            break;
        }
        if (this->number_of_times_each_philosopher_must_eat != -1 && meals_eaten >= this->number_of_times_each_philosopher_must_eat) {
            break; // Stop if meal limit reached
        }
        sleep();
    }
}

void Philosopher::join() {
    if (thread.joinable()) {
        thread.join();
    }
}