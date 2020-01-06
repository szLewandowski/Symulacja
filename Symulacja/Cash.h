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
	void RemoveCustomer(double);
	void WakeUpIfPossible(double);
private:
	int size();
	Process* cash_desks_[4]{};
	queue<Process*> queue_;
};

