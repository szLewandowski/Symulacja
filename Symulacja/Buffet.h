#pragma once
#include "process.h"
#include <vector>

class Buffet
{
public:
	Buffet();
	~Buffet();
	bool FreeSeats(const int);
	bool QueueEmpty();
	void AddToQueue(Process*);
private:
	static const int number_of_seats_ = 14;
	vector<Process*> seats_;
	queue<Process*> queue_;
};

