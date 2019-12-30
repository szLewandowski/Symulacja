#pragma once
#include "process.h"
#include "Customer.h"

class Cash
{
public:
	Cash();
	~Cash();
	bool free();
	void add_customer(Process*);
	void remove_customer(double);
private:
	int size();
	Process* cash_desks_[4];
};

