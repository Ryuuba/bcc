#include "BCCStatistics.h"

BCCStatistics::BCCStatistics() {
  arrivals = 0;
  blocked_arrivals = 0;
  blocking_probability = 0.0;
  simulation_time = 0.0;
}

void BCCStatistics::increase_blocked_arrivals() {
  blocked_arrivals++;
}

void BCCStatistics::increase_arrivals() {
  arrivals++;
}

void BCCStatistics::update_simtime(double time) {
  simulation_time = time; 
}

uint64_t BCCStatistics::get_arrivals() {
  return arrivals;
}

uint64_t BCCStatistics::get_blocked_arrivals() {
  return blocked_arrivals;
}

double BCCStatistics::get_arrival_rate() {
  return arrivals / simulation_time;
}

double BCCStatistics::get_blocked_arrival_rate() {
  return blocked_arrivals / simulation_time;
}

double BCCStatistics::get_simtime() {
  return simulation_time;
}

double BCCStatistics::erlang_b(uint16_t s, double a) {
  double ib = 1.0;
  for (uint16_t  i = 0; i <= s; i++)
    ib = 1.0 + i * ib / a;
  return 1.0/ib;
}

double BCCStatistics::get_blocking_prob() {
  return double(blocked_arrivals) / arrivals;
}