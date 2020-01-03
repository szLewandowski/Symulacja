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

bool Buffet::EnoughFreeSeats()
{
	int customers = 0;
	for (auto seat : seats_)
	{
		customers += seat->group_size_;
	}
	if(queue_.empty()==false)
	{
		if (queue_.front()->group_size_ <= number_of_seats_ - customers)
		{
			return true;
		}
		return false;
	}
	cerr << "ERROR Buffet.cpp: There is no process in queue\n";
	cin.get();
	return false;
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
	if (EnoughFreeSeats())
	{
		queue_.front()->execute();
	}
}

Process* Buffet::ReturnCustomer(double time)
{
	const auto it = find_if(seats_.begin(), seats_.end(), [&](Process* pr) {return  AreSame(time,pr->time()); });
	//Process* temp = *it;
	seats_.erase(it);
	return *it;
}
