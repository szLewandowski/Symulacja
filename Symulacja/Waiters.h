#pragma once
#include "process.h"
class Waiters
{
public:
	Waiters();
	~Waiters();
	bool Free() const;
	void Reservation();
	void EndReservation();
	void WaitersInfo();
private:
	static const int waiters_ = 7;
	int actual_;
};

