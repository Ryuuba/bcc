#include "Simulator.h"

Simulator::Simulator() {
  generator = nullptr;
  exponential = nullptr;
}

Simulator:~Simulator() {
  if (generator)
    delete generator;
  if (exponential)
    delete exponential;
}

unsigned get_queue_size() {
  return q.size();
}

Event Simulator::get_event() {
  Event ev(EventType::ARRIVAL, -1.0);
  if (!q.empty()){
    ev = q.top();
    q.pop();
  }
  return ev;
}

void Simulator::schedule_event(Event ev) {
  q.push(ev);
}