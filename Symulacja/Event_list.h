#ifndef SIMULATION_RESOURCES_QUEUE_TIME_EVENT_H_
#define SIMULATION_RESOURCES_QUEUE_TIME_EVENT_H_

#include <queue>
#include "event.h"
using namespace std;

class Event_list
{
  
public:
  Event_list() = default;
  ~Event_list() = default;
  void AddNewEvent(Event* add_event);
  int GetId();
  Event* First();
  void PrintEventList();
  void DeleteEvent(int id);
  double GetTime();
private:
  Event* first_ = nullptr;
  Event* last_ = nullptr;
  int id_ = 0;
};
#endif //QUEUE_TIME_EVENT_H
