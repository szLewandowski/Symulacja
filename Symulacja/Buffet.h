#pragma once
#include "process.h"
#include <vector>

class Buffet
{
public:
	Buffet();
	~Buffet();
	bool AreSame(double, double) const;
	bool FreeSeats(int);
	bool QueueEmpty();
	void AddToQueue(Process*);
	void AddToBuffet();
	void WakeUpIfPossible();
	Process* ReturnCustomer(double);
private:
	static const int number_of_seats_ = 14;
	vector<Process*> seats_;
	queue<Process*> queue_;
};

