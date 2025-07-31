    #pragma once

    #include <gpiod.hpp>
    #include <iostream>
    #include <thread>
    #include <mutex>
    #include <chrono>
    #include <vector>
    #include <memory>
    #include <atomic>


    #include "gpioManager.h"

    class Philosopher{
        private:
        int id; //we will use gpio num for id
        std::string name;
   
        int time_to_die;
        int time_to_eat;
        int time_to_sleep;
        int number_of_times_each_philosopher_must_eat;

        std::thread thread; //philosopher
        std::shared_ptr<std::mutex> left; // left fork
        std::shared_ptr<std::mutex> right;// right fork

        std::unique_ptr<GpioManager> gpio;
        std::atomic<bool>& stop;// each thread has access to this object without data race possible

        public:
        Philosopher(const std::string& name,int id,int time_to_die,int time_to_eat, int time_to_sleep,
                    int number_of_times_each_philosopher_must_eat,std::atomic<bool>& stop,std::shared_ptr<std::mutex> left, std::shared_ptr<std::mutex> right);

        void start(); //start thread
        void join(); // wait for thread
        void run();

        void think();
        void eat();
        void sleep();
    };
