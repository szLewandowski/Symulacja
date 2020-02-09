#include "Cash.h"
#include <iostream>
#include "fstream"

Cash::Cash()
{
	std::cerr << "Make Cash\n";
	for (int i = 0; i < 4; ++i)
		cash_desks_[i] = 0;
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
		if (cash_desks_[i] != 0)cash_desk_size++;
	cout << "Zajete stanowiska kas: " << cash_desk_size<<endl;
}

void Cash::AddCustomerToCash(const double time)
{
	for (int i = 0; i < 4; ++i)
	{
		if (cash_desks_[i] == 0)
		{
			cash_desks_[i] = queue_.front()->id_;
			queue_.pop();
			ofstream d_output("punkt_d.txt", ios::app);
			d_output << time << " " << queue_.size() << endl;
			d_output.close();
			return;
		}
	}
	cerr << "ERROR Cash: There is no free cash desk!\n";
	cin.get();
}

void Cash::AddCustomerToQueue(Process* customer, const double time)
{
	queue_.push(customer);
	ofstream d_output("punkt_d.txt", ios::app);
	d_output << time << " " << queue_.size() << endl;
	d_output.close();
}

void Cash::RemoveCustomer(Process* customer)
{
	for (int i = 0; i < 4; ++i)
	{
		if (cash_desks_[i] == customer->id_)
		{
			cash_desks_[i] = 0;
			return;
		}
	}
	cerr << "ERROR Cash.cpp: There is no consumer to remove!\n";
	cin.get();
}

void Cash::WakeUpIfPossible(const double new_time)
{
	if (queue_.empty() == false && Free())
	{
		queue_.front()->execute(new_time);
	}
}

void Cash::Alarm(const double time)
{
	if (queue_.empty() == false)
	{
		for (int i = 0; i < static_cast<int>(queue_.size()); ++i)
		{
			Process* temp = queue_.front();
			queue_.pop();
			if (rand() % 10 < 3)
			{
				ofstream d_output("punkt_d.txt", ios::app);
				d_output << time << " " << queue_.size() << endl;
				d_output.close();
				delete temp;
			}
			else
			{
				queue_.push(temp);
			}
		}
	}
}

void Cash::Cleaning(vector<int>* id)
{
	for (auto it = id->begin(); it != id->end(); ++it)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (cash_desks_[i] == *it)
			{
				cash_desks_[i] = 0;
			}
		}
	}
}

int Cash::size()
{
	int counter = 4;
	for (int i = 0; i < 4; ++i)
	{
		if (cash_desks_[i] == 0)--counter;
	}
	return counter;
}
