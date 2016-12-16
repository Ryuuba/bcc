#include "BCCSimulator.h"

BCCSimulator::BCCSimulator(const char* filename) {
  std::ifstream ifs(filename, std::ifstream::in);
  if (ifs.is_open()) {
    state_j = 0;
    ifs >> seed 
        >> offered_traffic
        >> call_arrival_rate
        >> mean_lifetime
        >> start_time
        >> total_arrivals
        >> channels;
    schedule_event(EventType::ARRIVAL, start_time);
    generator = new std::minstd_rand0(seed);
    t_arrival = new std::exponential_distribution<double>(call_arrival_rate);
    t_live = new std::exponential_distribution<double>(mean_lifetime);
    ifs.close();
  }
  //TODO: Try this part as an exception
  else std::cerr << "Unable to open " << filename << std::endl;
}

void BCCSimulator::start() {
  bool next = true;
  double time = 0.0;
  while (statistics.get_arrivals() < total_arrivals && next) {
    Event ev = get_event();
    //std::cout << "Processing: " << ev << std::endl;
    statistics.update_simtime(ev.second);
    if (ev.first == EventType::ARRIVAL) {
      statistics.increase_arrivals();
      time = (*t_arrival)(*generator);
      //std::cout << "Arrival Time: " << time << std::endl; 
      ev.second = time + statistics.get_simtime();
      schedule_event(ev);
      if (state_j < channels) {
        state_j++;
        ev.first = EventType::DEPARTURE;
        time = (*t_live)(*generator);
        //std::cout << "Departure Time: " << time << std::endl; 
        //std::cout << "Channels in used: " << state_j << std::endl;
        ev.second = time + statistics.get_simtime();
        schedule_event(ev);
      }
      else statistics.increase_blocked_arrivals();
    }
    else {
      state_j--;
      //std::cout << "Channels in used: " << state_j << std::endl;
    }
    //std::cout << "Simulation time:" << ' '
              //<< statistics.get_simtime() << '\n'
              //<< "Queue size: " << get_queue_size() << std::endl;
    //std::cin >> next;
  }
}

void BCCSimulator::compute_statistics(const char* filename) {
  std::ofstream ofs(filename, std::ofstream::out);
  if (ofs.is_open()) {
    ofs << "Simulation time: " << statistics.get_simtime() << '\n'
        << "Arrivals: " << statistics.get_arrivals() << '\n'
        << "Blocked arrivals: " << statistics.get_blocked_arrivals() << '\n'
        << "Arrival rate: " << statistics.get_arrival_rate() << '\n'
        << "Blocked arrival rate: " << statistics.get_blocked_arrival_rate() << '\n'
        << "Blocking probability: " << statistics.get_blocking_prob() << '\n'
        << "Erlang-B: " << statistics.erlang_b(channels, offered_traffic);
   ofs.close();

  }
  else std::cerr << "Unable to open " << filename << std::endl;
}