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

bool Cash::Free()
{
	if (size() < 4)return true;
	return false;
}

bool Cash::AreSame(const double a, const double b) const
{
	return fabs(a - b) < DBL_EPSILON;
}

void Cash::CashInfo()
{
	cout << "\nCash info:\n";
	cout << "Kolejka do kasy: " << queue_.size()<<endl;
	int cash_desk_size = 0;
	for (int i = 0; i < 4; ++i)
		if (cash_desks_[i] != nullptr)cash_desk_size++;
	cout << "Zajete stanowiska kas: " << cash_desk_size<<endl;
}

void Cash::AddCustomerToCash()
{
	for (int i = 0; i < 4; ++i)
	{
		if (cash_desks_[i] == nullptr)
		{
			cash_desks_[i] = queue_.front();
			queue_.pop();
			return;
		}
	}
	cerr << "ERROR Cash: There is no free cash desk!\n";
	cin.get();
}

void Cash::AddCustomerToQueue(Process* customer)
{
	queue_.push(customer);
}

void Cash::RemoveCustomer(const double clock)
{
	for (int i = 0; i < 4; ++i)
	{
		if (cash_desks_[i] != nullptr && AreSame(cash_desks_[i]->time(), clock))
		{
			cash_desks_[i] = nullptr;
			return;
		}
	}
	cerr << "ERROR Cash.cpp: There is no consumer to remove!\n";
	cin.get();
}

void Cash::WakeUpIfPossible()
{
	if(queue_.empty()==false)
	{
		queue_.front()->execute();
	}
}

int Cash::size()
{
	int counter = 4;
	for (int i = 0; i < 4; ++i)
	{
		if (cash_desks_[i] == nullptr)--counter;
	}
	return counter;
}
