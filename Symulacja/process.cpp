#include "process.h"

Process::Process(Event_list* list,int id): phase_(0), terminated_(false),event_list_(list),id_(++id)
{
	cerr << "\nProcess: New process created!";
	my_event_ = new Event(this);
}

Process::~Process()
{
	cout << "Process destruktor\n";
	delete my_event_;
}

double Process::time()
{
	return my_event_->event_time_;
}

void Process::Info()
{
	cout << "\nID: " << id_ << "  FAZA: " << phase_ << "   ROZMAR GRUPY: " << group_size_ << endl;
}

void Process::activate(const double time)
{
	cout << "\nscheduled time: " << time << endl;
	my_event_->event_time_ = time;
	event_list_->AddNewEvent(my_event_);
}

