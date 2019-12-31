#include "process.h"
#include "Event_list.h"
#include <iostream>

Process::Process(Event_list* list): phase_(0), terminated_(false),event_list_(list)
{
	cerr << "Process: New process created!\n";
	my_event_ = new Event(this);
}

Process::~Process()
{
	delete my_event_;
}

double Process::time()
{
	return my_event_->event_time_;
}

void Process::activate(const double time)
{
	my_event_->event_time_ = time;
	event_list_->AddNewEvent(my_event_);
}
