#ifndef BCC_SIM_H
#define BCC_SIM_H

#include <fstream>
#include "Simulator.h"
#include "BCCStatistics.h"

class BCCSimulator: public Simulator{
  private:
    double offered_traffic;
    double call_arrival_rate;
    double mean_lifetime;
    double start_time;
    uint64_t total_arrivals;
    uint32_t channels;
    uint16_t state_j;
    BCCStatistics statistics;
  public:
    BCCSimulator(const char*);
    virtual void start();
    virtual void compute_statistics(const char*);
};

#endif