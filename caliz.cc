#include <queue>
#include <iostream>

#include "Event.h"

int main(){
  std::priority_queue<Event,std::vector<Event>,CompareEvent> q;
  Event ev(EventType::ARRIVAL, 130.1);
  for (unsigned i = 0 ; i < 10; i++) {
    ev.second -= double(i);
    q.push(ev);
  }
  while (!q.empty()) {
    std::cout << q.top() << '\n';
    q.pop();
  }
  std::cout << std::endl;
  return 0;
}