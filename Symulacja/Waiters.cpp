#include "Waiters.h"
#include <iostream>

Waiters::Waiters():actual_(0)
{
	std::cerr << "Make Waiters\n";
}

Waiters::~Waiters()
{
	std::cerr << "Delete Waiters\n";
}

bool Waiters::Free() const
{
	if (actual_ >= waiters_)
	{
		return false;
	}
	return true;
}

void Waiters::Reservation()
{
	++actual_;
	if (actual_ > waiters_) {
		cerr << "ERROR Waiters.cpp: You can not make a reservation!\n";
		cin.get();
	}
}

void Waiters::EndReservation()
{
	--actual_;
}

void Waiters::WaitersInfo()
{
	cout << "\nWaiters info:\n";
	cout << "Zajeci kelnerzy: " << actual_ << "/" << waiters_ << endl;
}
