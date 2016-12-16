#include "Simulator.h"

Simulator::Simulator() {
  generator = nullptr;
  t_arrival = nullptr;
  t_live = nullptr;
}

Simulator::~Simulator() {
  if (generator)
    delete generator;
  if (t_arrival)
    delete t_arrival;
  if (t_live)
    delete t_live;
}

void Simulator::schedule_event(Event ev) {
  //std::cout << ev << std::endl;
  q.push(ev);
}

void Simulator::schedule_event(EventType evt, double time) {
  Event ev(evt, time);
  //std::cout << ev << std::endl;
  q.push(ev);
}

unsigned Simulator::get_queue_size() {
  return q.size();
}

Event Simulator::get_event() {
  Event ev(EventType::ARRIVAL, -1.0);
  if (!q.empty()) {
    ev = q.top();
    q.pop();
  }
  return ev;
}