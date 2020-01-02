#include "Buffet.h"
#include <iostream>
#include <algorithm>

Buffet::Buffet()
{
	std::cerr << "Make Buffet\n";	
}

Buffet::~Buffet()
{
	std::cerr << "Delete Buffet\n";
}

bool Buffet::AreSame(const double a, const double b) const
{
	return fabs(a - b) < DBL_EPSILON;
}

bool Buffet::FreeSeats(const int need)
{
	int customers = 0;
	for (auto seat : seats_)
	{
		customers += seat->group_size_;
	}
	return (number_of_seats_-customers)>=need;
}

bool Buffet::QueueEmpty()
{
	return queue_.empty();
}

void Buffet::AddToQueue(Process* customer)
{
	queue_.push(customer);
}

void Buffet::AddToBuffet()
{
	seats_.push_back(queue_.front());
	queue_.pop();
}

void Buffet::WakeUpIfPossible()
{
	cin.get();
}

Process* Buffet::ReturnCustomer(double time)
{
	const auto it = find_if(seats_.begin(), seats_.end(), [&](Process* pr) {return  AreSame(time,pr->time()); });
	//Process* temp = *it;
	seats_.erase(it);
	return *it;
}
