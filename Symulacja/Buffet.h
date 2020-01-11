#pragma once
#include "process.h"
#include <vector>

class Buffet
{
public:
	Buffet();
	~Buffet();
	bool AreSame(double, double) const;
	void BuffetInfo();
	bool EnoughFreeSeats();
	int QueueSize();
	void AddToQueue(Process*);
	void AddToBuffet();
	void WakeUpIfPossible(double);
	void ReturnCustomer(int);
	void Alarm();
	void Cleaning(vector<int>*);
private:
	static const int number_of_seats_ = 14;
	int seats_[number_of_seats_] = {};
	queue<Process*> queue_;
};

