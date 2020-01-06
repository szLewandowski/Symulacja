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

void Buffet::BuffetInfo()
{
	cout << "\nBuffet info:\n";
	cout << "Kolejak do bufetu: " << queue_.size()<<endl;
	cout << "Procesów w bufecie: " << seats_.size() << endl;
	int customers = 0;
	for (auto seat : seats_)
	{
		customers += seat->group_size_;
	}
	cout << "Zajete miejsca w bufecie: " << customers << endl;
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
	}
	return false;
}

int Buffet::QueueSize()
{
	return static_cast<int>(queue_.size());
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

void Buffet::WakeUpIfPossible(const double new_time)
{
	for (int i = 0; i < 4; ++i) {
		if (EnoughFreeSeats() == true)
		{
			queue_.front()->execute(new_time);
		}
	}
}

void Buffet::ReturnCustomer(double time)
{
	const auto it = find_if(seats_.begin(), seats_.end(), [&](Process* pr) {return  AreSame(time,pr->time()); });
	seats_.erase(it);
}
