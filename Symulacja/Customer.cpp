#include "Customer.h"
#include <iostream>
#include <random>

Customer::Customer(Event_list* list,Restaurant* restaurant): Process(list)
{
	restaurant_ = restaurant;
	//cerr << "Customer constructor\n";
}

void Customer::execute()
{
	auto active = true;
	while(active)
	{
		switch(phase_)
		{
		case 0:
		{
			cerr << "--> Pojawienie sie nowej grupy klientow";
			Process* process = new Customer(event_list_,restaurant_);
			process->activate(time() + NormalDistributionGenerator(make_pair(1900, 200)));
			process = nullptr;
			if (rand() % 2 == 0)
			{
				//buffet group
				restaurant_->buffet_->AddToQueue(this);
				if(restaurant_->buffet_->QueueEmpty() && restaurant_->buffet_->FreeSeats(this->group_size_))
				{
					phase_ = 9;
				}
				else
				{
					active = false;
				}
			}
			else
			{
				//restaurant group
				restaurant_->tables_->AddToQueue(this);
				
			}
			
		}
			break;
		case 1:
			cerr << "Poczatek obslugi przez managera";
			break;
		case 2:
			cerr << "Koniec obslugi przez managera";
			break;
		case 3:
			cerr << "Kelner podaje napoj";
			break;
		case 4:
			cerr << "Kelner podaje danie glowne";
			break;
		case 5:
			cerr << "Rozpoczecie konsumpcji";
			break;
		case 6:
			cerr << "Koniec konsumpcji";
			break;
		case 7:
			cerr << "Rozpoczecie obslugi przy kasie";
			break;
		case 8:
			cerr << "Koniec obslugi przy kasie";
			break;
		case 9:
			cerr << "Poczatek obslugi w bufecie";
			break;
		case 10:
			cerr << "Koniec obslugi w bufecie";
			break;			
		}
	}
}

double Customer::NormalDistributionGenerator(const pair<const int, const int> p)
{
	static default_random_engine generator;
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}

double Customer::ExponentialDistributionGenerator(const int average)
{
	static default_random_engine generator;
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}
