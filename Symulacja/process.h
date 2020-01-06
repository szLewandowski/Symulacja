#pragma once
#include "Event_list.h"
#include <iostream>

class Process
{
public:
	Process(Event_list*,int);
	~Process();
	void virtual execute(double) = 0;
	double time();
	void Info();
	void activate(double);
	int id_;
	int phase_;
	bool terminated_;
	const int group_size_ = (rand() % 4) + 1;
	Event_list* event_list_;
	void TimeUpdate(double);
private:
	Event* my_event_;
	
};

