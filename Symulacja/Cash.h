#pragma once
#include "process.h"


class Cash
{
public:
	Cash();
	~Cash();
	bool free();
	void AddCustomerToCash(Process*);
	void AddCustomerToQueue(Process*);
	void RemoveCustomer(double);
private:
	int size();
	Process* cash_desks_[4];
	queue<Process*> queue_;
};

