#include "Buffet.h"
#include <iostream>
#include <algorithm>

Buffet::Buffet()
{
	std::cerr << "Make Buffet\n";
	for (int i = 0; i < number_of_seats_; ++i)
	{
		seats_[i] = 0;
	}
}

Buffet::~Buffet()
{
	std::cerr << "Delete Buffet\n";
}

bool Buffet::AreSame(const double a, const double b) const
{
	return fabs(a - b) < DBL_EPSILON;
}

void Buffet::BuffetInfo()
{
	cout << "\nBuffet info:\n";
	cout << "Kolejak do bufetu: " << queue_.size()<<endl;
	int seats_counter = 0;
	for (int i = 0; i < number_of_seats_; ++i)
	{
		if (seats_[i] != 0)seats_counter++;
	}
	cout << "Zajete miejsca w bufecie: " << seats_counter << "/" << number_of_seats_ << endl;
}

bool Buffet::EnoughFreeSeats()
{
	int seats_counter = 0;
	for (int i = 0; i < number_of_seats_; ++i)
	{
		if (seats_[i] != 0)seats_counter++;
	}
	if(queue_.empty()==false)
	{
		if (queue_.front()->group_size_ <= number_of_seats_ - seats_counter)
		{
			return true;
		}
	}
	return false;
}

int Buffet::QueueSize()
{
	return static_cast<int>(queue_.size());
}

void Buffet::AddToQueue(Process* customer)
{
	queue_.push(customer);
}

void Buffet::AddToBuffet()
{
	if(queue_.empty()==false)
	{
		int counter = 0;
		for (int i = 0; i < number_of_seats_; ++i)
		{
			if (counter < queue_.front()->group_size_ && seats_[i] == 0)
			{
				seats_[i] = queue_.front()->id_;
				counter++;
			}
		}
		queue_.pop();
	}
}

void Buffet::WakeUpIfPossible(const double new_time)
{
	for (int i = 0; i < 4; ++i) {
		if (EnoughFreeSeats() == true)
		{
			queue_.front()->execute(new_time);
		}
	}
}

void Buffet::ReturnCustomer(const int id)
{
	for (int i = 0; i < number_of_seats_; ++i)
	{
		if (seats_[i] == id)
		{
			seats_[i] = 0;
		}
	}
}

void Buffet::Alarm()
{
	if (queue_.empty() == false)
	{
		for (int i = 0; i < static_cast<int>(queue_.size()); ++i)
		{
			Process* temp = queue_.front();
			queue_.pop();
			if (rand() % 10 < 3)
			{
				delete temp;
			}
			else
			{
				queue_.push(temp);
			}
		}
	}
}

void Buffet::Cleaning(vector<int>* id)
{
	for (auto it = id->begin(); it != id->end(); ++it)
	{
		for (int i = 0; i < number_of_seats_; ++i)
		{
			if(seats_[i]==*it)
			{
				seats_[i] = 0;
			}
		}
	}
}
