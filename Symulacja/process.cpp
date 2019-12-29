#include "process.h"

Process::Process(): phase_(0), terminated_(false)
{
}

double Process::time()
{
	return my_event_->event_time_;
}

void Process::activate(double)
{
}
