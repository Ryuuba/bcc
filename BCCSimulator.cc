#include "BCCSimulator.h"

BCCSimulator::BCCSimulator(const char* filename) {
  std::ifstream ifs(filename, std::ifstream::in);
  if (ifs.is_open()) {
    state_j = 0;
    ifs >> seed 
        >> offered_traffic
        >> call_arrival_rate
        >> start_time
        >> total_arrivals
        >> channels;
    schedule_event(EventType::ARRIVAL, start_time);
    generator = new std::minstd_rand0(seed);
    exponential = new std::exponential_distribution<double>(call_arrival_rate);
    ifs.close();
  }
  else std::cerr << "Unable to open " << filename << std::endl;
}

void BCCSimulator::start() {
  while (total_arrivals < statistics.get_arrivals()) {
    Event ev = get_event();
    statistics.add_time(ev.second);
    if (ev.first == EventType::ARRIVAL) {
      statistics.increase_arrivals();
      ev.second = *exponential(*generator) + statistics.get_sim_time();
      schedule_event(ev);
      if (state_j < channels) {
        state_j++;
        ev.first = EventType::DEPARTURE;
        ev.second = *exponential(*generator) + statistics.get_sim_time();
        schedule_event(ev);
      }
      else statistics.increase_blocked_arrivals();
    }
    else state_j--;
  }
}

void BCCSimulator::compute_statistics(const char* filename) {
  std::ofstream ofs(filename, std::ofstream::out);
  if (ofs.is_open()) {
    ofs << "Simulation time: " << statistics.get_sim_time() << '\n'
        << "Arrivals: " << statistics.get_arrivals() << '\n'
        << "Blocked arrivals: " << statistics.get_blocked_arrivals() << '\n'
        << "Arrival rate: " << statistics.get_arrival_rate() << '\n'
        << "Blocked arrival rate: " << statistics.blocked_arrival_rate() << '\n'
        << "Blocking probability: " << statistics.get_blocking_probability() << '\n'
        << "Erlang-B: " << statistics.erlang_b(channels, offered_traffic);
   ofs.close();

  }
  else std::cerr << "Unable to open " << filename << std::endl;
}