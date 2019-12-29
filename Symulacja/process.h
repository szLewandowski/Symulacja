#pragma once
#include "event.h"

class Process
{
public:
	Process();
	virtual ~Process() = 0;
	void virtual execute() = 0;
	double time();
	void activate(double);
	int phase_;
	bool terminated_;
private:
	Event* my_event_;
};

