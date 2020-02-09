#include "process.h"

Process::Process(Event_list* list,int id): phase_(0), terminated_(false),event_list_(list),id_(++id)
{
	cerr << "\nProcess: New process created!";
	my_event_ = new Event(this);
	const int random = rand() % 9;
	if(random==0)
	{
		group_size_ = 1;
	}
	else if (random>0 && random<4)
	{
		group_size_ = 2;
	}
	else if(random>3 && random<7)
	{
		group_size_ = 3;
	}
	else
	{
		group_size_ = 4;
	}
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
	cout << "\nID: " << id_ << "  FAZA: " << phase_ << "   ROZMAR GRUPY: " << group_size_ << "   CZAS: " << time()<< endl;
}

void Process::activate(const double time)
{
	cout << "\nscheduled time: " << time << endl;
	my_event_->event_time_ = time;
	event_list_->AddNewEvent(my_event_);
}

void Process::TimeUpdate(const double new_time)
{
	my_event_->event_time_ = new_time;
}

