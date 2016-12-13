#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <queue>
#include <random>
#include <functional>
#include <cstdint>
#include <algorithm>
#include <iostream>

#include "Event.h"

class Simulator {
  protected:
    std::priority_queue<Event,std::vector<Event>,CompareEvent> q;
    unsigned seed;
    std::minstd_rand0* generator;
    std::exponential_distribution<double>* exponential;
  public:
    Simulator();
    virtual ~Simulator();
    virtual Event get_event();
    virtual void schedule_event(Event);
    virtual unsigned get_queue_size();
    virtual double compute_statistics(const char*) = 0;
};

#endif