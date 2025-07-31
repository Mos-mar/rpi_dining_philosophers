#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>


#include "gpioManager.h"
#include "dinerManager.h"
#include "philosopher.h"




//5 ARGUMENTS MAX EXPECTED AT ALL TIMES
int main(int argc, char** argv) {  

//Follow order of declaration to initiate the arguments of the program
    int number_of_philosophers = std::stoi(argv[1]);
    int time_to_die = std::stoi(argv[2]);
    int time_to_eat = std::stoi(argv[3]);
    int time_to_sleep = std::stoi(argv[4]);
    int number_of_times_each_philosopher_must_eat= std::stoi(argv[5]);
    
    DinerManager diner(number_of_philosophers,time_to_die,time_to_eat,time_to_sleep,number_of_times_each_philosopher_must_eat);
    diner.startAll();
    diner.joinAll();
    diner.stopAll();


 
}



