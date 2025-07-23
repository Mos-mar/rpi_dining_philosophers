#include "philosopher.h"


Philosopher::Philosopher
(std::string name,int id, int number_of_philosophers, int time_to_die, int time_to_eat,int time_to_sleep,
     int number_of_times_each_philosopher_must_eat,std::atomic<bool>& stop,std::shared_ptr<std::mutex> left, std::shared_ptr<std::mutex> right)

: name(name), id(id), number_of_philosophers(number_of_philosophers), time_to_die(time_to_die),
time_to_sleep(time_to_sleep),
number_of_times_each_philosopher_must_eat(number_of_times_each_philosopher_must_eat),
stop(stop),left(left), right(right)
{
    gpio = std::make_unique<GpioManager>();
    gpio->init_pin(id, name);
}



void Philosopher::think()
{
    this->gpio->set_high(this->id);
}


void Philosopher::eat()
{
     std::scoped_lock(*left,*right);
     this->gpio->blink(this->id,this->number_of_times_each_philosopher_must_eat,this->time_to_eat);
}

void Philosopher::sleep()
{
    this->gpio->set_low(this->id);
    std::this_thread::sleep_for(std::chrono::milliseconds(this->time_to_sleep));
}

void Philosopher::start()
{
  this->thread = std::thread(&Philosopher::run,this);
}

void Philosopher::run()
{
    while(!this->stop)
    {
      this->eat();
      this->think();
      this->sleep();
    }
}

void Philosopher::join()
{
    if(this->thread.joinable())
    {
        this->thread.join();
    }
}