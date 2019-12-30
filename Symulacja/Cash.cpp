#include "Cash.h"
#include <iostream>

Cash::Cash()
{
	std::cerr << "Make Cash\n";
	for (int i = 0; i < 4; ++i)
		cash_desks_[i] = nullptr;
}

Cash::~Cash()
{
	std::cerr << "Delete Cash\n";
}

bool Cash::free()
{
	if (size() < 4)return true;
	return false;
}

void Cash::add_customer(Process* customer)
{
	for(int i=0;i<4;++i)
	{
		if(cash_desks_[i]==nullptr)
		{
			cash_desks_[i] = customer;
			return;
		}
	}
}

void Cash::remove_customer(const double clock)
{
	for(int i=0;i<4;++i)
	{
		if(cash_desks_[i]!=nullptr && cash_desks_[i]->time()<=clock) //double types comparison 
		{
			delete cash_desks_[i];
			cash_desks_[i] = nullptr;
			return;
		}
	}
	cerr << "ERROR (Cash class) There is no consumer to remove!\n";
	cin.get();
}

int Cash::size()
{
	int counter = 4;
	for(int i=0;i<4;++i)
	{
		if (cash_desks_[i] == nullptr)--counter;
	}
	return counter;
}
