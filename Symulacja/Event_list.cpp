#include "Event_list.h"
#include <ostream>
#include <iostream>
#include "event.h"
using namespace std;

void Event_list::AddNewEvent(Event* add_event)
{

  cout << "Add time event:  " << endl;
  add_event->ShowParameter();
  cout << "--------------------" << endl;
  if (first_ == nullptr) //If list is empty add event on first
  {
    first_ = last_ = add_event;
    return;
  }
  else if (add_event->Time() <= first_->Time()) //Add event on beginning
  {
    first_->prev_ = add_event;
    add_event->next_ = first_;
    first_ = add_event;
    return;
  }
  else if (add_event->Time() >= last_->Time()) //Add event on end
  {
    add_event->prev_ = last_;
    last_->next_ = add_event;
    last_ = add_event;
    return;
  }
  else {

    Event_list* search_ = first_;
    while (search_->Time() <= add_event->Time())
    {

      search_ = search_->next_;
    }
    add_event->next_ = search_;
    add_event->prev_ = search_->prev_;
    search_->prev_->next_ = add_event;
    search_->prev_ = add_event;

  }
}
void Event_list::DeleteEvent(int id)
{
  if (first_->GetId() == id)
  {
    if (first_ == last_)
    {
      Event* event_to_delete = first_;
      first_ = last_ = nullptr;
      delete event_to_delete;
      return;
    }
    else
    {
      Event* event_to_delete = first_;
      first_ = first_->next_;
      first_->prev_ = nullptr;
      delete event_to_delete;
      return;
    }
  }
  if (last_->GetId() == id)
  {
    Event* event_to_delete = last_;
    last_ = last_->prev_;
    last_->next_ = NULL;
    delete event_to_delete;
    return;
  }
  bool found = true;
  Event* search = first_;
  cout << search << endl;
  search->ShowParameter();
  while (search->GetId() != id)
  {
    if (search->next_ == nullptr)
    {
      found = false;
      break;
    }
    search = search->next_;
  }
  if (found == true)
  {
    search->next_->prev_ = search->prev_;
    search->prev_->next_ = search->next_;
    delete search;
  }

}

double Event_list::GetTime()
{
  return first_->Time();
}

Event* Event_list::First()
{
  Event* first_event_from_list = first_;
  first_ = first_->next_;
  return first_event_from_list;
}

void Event_list::PrintEventList()
{
  Event* print_ = first_;
  cout << "LIST TIME EVENT" << endl;
  while (print_) {
    print_->ShowParameter();
    print_ = print_->next_;
  }
  cout << "*******" << endl;
}

int Event_list::GetId()
{
  id_++;
  return id_;
}


