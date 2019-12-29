#pragma once

class Process;

class Event
{
public:
	Event(Process* ptr);
	~Event();
	double event_time_;
	Process* proc_;
	
};

