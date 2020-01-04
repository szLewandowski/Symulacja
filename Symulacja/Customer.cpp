#include "Customer.h"
#include <iostream>
#include <random>

Customer::Customer(Event_list* list,Restaurant* restaurant,int id): Process(list,id)
{
	restaurant_ = restaurant;
	//cerr << "Customer constructor\n";
}

void Customer::execute()
{
	Info();
	auto active = true;
	while(active)
	{
		switch (phase_)
		{
		case 0:
		{
			cerr << "\n--> Faza 0: Pojawienie sie nowej grupy klientow";
			Process* process = new Customer(event_list_, restaurant_,id_);
			process->activate(time() + NormalDistributionGenerator(make_pair(1300, 200)));
			process = nullptr;
			if (true)//(rand() % 2 == 0)
			{
				//buffet group
				restaurant_->buffet_->AddToQueue(this);
				phase_ = 9;
				if (restaurant_->buffet_->EnoughFreeSeats() == false || restaurant_->buffet_->QueueSize() > 1)
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
			{
				cerr << "\n--> Faza 7: Rozpoczecie obslugi przy kasie";
				restaurant_->cash_->AddCustomerToCash();
				activate(time() + ExponentialDistributionGenerator(200));
				phase_ = 8;
				active = false;
			}
			break;
		case 8:
			{
				cerr << "\n--> Faza 8: Koniec obslugi przy kasie";
				restaurant_->cash_->RemoveCustomer(time());
				restaurant_->cash_->WakeUpIfPossible();
				terminated_ = true;
				active = false;
			}
			break;
		case 9:
			{
				cerr << "\n--> Faza 9: Poczatek obslugi w bufecie ";
				restaurant_->buffet_->AddToBuffet();
				activate(time() + NormalDistributionGenerator(make_pair(3200, 100)));
				phase_ = 10;
				active = false;
			}
			break;
		case 10:
			{
				cerr << "\n--> Faza 10: Koniec obslugi w bufecie";
				restaurant_->buffet_->ReturnCustomer(time());
				restaurant_->cash_->AddCustomerToQueue(this);
				restaurant_->buffet_->WakeUpIfPossible();
				phase_ = 7;
				if(restaurant_->cash_->Free()==false)
				{
					active = false;
				}
			}
			break;			
		}
	}
	restaurant_->buffet_->BuffetInfo();
	restaurant_->cash_->CashInfo();
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
