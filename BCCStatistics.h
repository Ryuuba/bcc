#ifndef BCC_STATISTICS_H
#define BCC_STATISTICS_H

#include <cstdint>

class BCCStatistics{
  private:
    uint64_t arrivals;
    uint64_t blocked_arrivals;
    double blocking_probability, simulation_time;
  public:
    BCCStatistics();
    virtual ~BCCStatistics(){}
    virtual void increase_blocked_arrivals();
    virtual void increase_arrivals();
    virtual void add_time(double);
    uint64_t get_arrivals();
    uint64_t get_locked_arrivals();
    double get_arrival_rate();
    double get_blocked_arrival_rate();
    double get_sim_time();
    double get_blocking_prob();
    double erlang_b(uint16_t, double);
};

#endif