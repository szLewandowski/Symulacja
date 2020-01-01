#include "Buffet.h"
#include <iostream>

Buffet::Buffet()
{
	std::cerr << "Make Buffet\n";	
}

Buffet::~Buffet()
{
	std::cerr << "Delete Buffet\n";
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
