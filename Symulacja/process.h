#pragma once
#include "Event_list.h"
#include <iostream>

class Process
{
public:
	Process(Event_list*);
	~Process();
	void virtual execute() = 0;
	double time();
	void activate(double);
	int phase_;
	bool terminated_;
	Event_list* event_list_;
private:
	Event* my_event_;
};

