#pragma once
#include "process.h"


class Cash
{
public:
	Cash();
	~Cash();
	bool Free();
	bool AreSame(double, double) const;
	void CashInfo();
	void AddCustomerToCash();
	void AddCustomerToQueue(Process*);
	void RemoveCustomer(Process*);
	void WakeUpIfPossible(double);
	void Alarm();
	void Cleaning(vector<int>*);
private:
	int size();
	int cash_desks_[4]{};
	queue<Process*> queue_;
};

