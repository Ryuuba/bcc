#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <queue>
#include <random>
#include <cstdint>
#include <iostream>

#include "Event.h"

class Simulator {
  private:
    std::priority_queue<Event,std::vector<Event>,CompareEvent> q;
  protected:
    unsigned seed;
    std::minstd_rand0* generator;
    std::exponential_distribution<double>* t_arrival;
    std::exponential_distribution<double>* t_live;
  public:
    Simulator();
    virtual ~Simulator();
    virtual Event get_event();
    virtual void schedule_event(Event);
    virtual void schedule_event(EventType, double);
    virtual unsigned get_queue_size();
    virtual void compute_statistics(const char*) = 0;
};

#endif