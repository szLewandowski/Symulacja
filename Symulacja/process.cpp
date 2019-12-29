#include "process.h"

Process::Process(): phase_(0), terminated_(false)
{
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

void Process::activate(double)
{
	// uzupelniæ!
}
