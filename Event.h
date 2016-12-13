#ifndef EVENT_H
#define EVENT_H

#include <utility>
#include <iostream>

enum class EventType : uint8_t {
      ARRIVAL = 0, DEPARTURE
};

typedef std::pair<EventType, double> Event;

class CompareEvent {
  public:
    bool operator() (const Event& lhs, const Event& rhs) {
      return lhs.second > rhs.second;
  }
};

inline std::ostream& operator << (std::ostream& os, const Event& ev) {
  if (ev.first == EventType::ARRIVAL)
    os << "arrival at " << ev.second << " time unit";
  else 
    os << "departure at " << ev.second << " time unit";
  return os;
}

#endif