#include "Manager.h"
#include <iostream>

Manager::Manager():is_free_(true)
{
	std::cerr << "Make Manager\n";
}

Manager::~Manager()
{
	std::cerr << "Delete Manager\n";
}

bool Manager::Free() const
{
	return is_free_;
}

void Manager::Reservation()
{
	is_free_ = false;
}

void Manager::EndReservation()
{
	is_free_ = true;
}
