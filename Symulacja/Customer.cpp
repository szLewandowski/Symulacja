#include "Customer.h"
#include <iostream>
#include <random>
#include "fstream"

Customer::Customer(Event_list* list,Restaurant* restaurant,int id): Process(list,id)
{
	restaurant_ = restaurant;
	//cerr << "Customer constructor\n";
}

void Customer::execute(const double new_time)
{
	TimeUpdate(new_time);
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
			process->activate(time() + NormalDistributionGenerator(make_pair(500, 100)));
			process = nullptr;
			if (rand() % 2 == 0)
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
				restaurant_->tables_->AddToQueue(this, time());
				queue_for_tables_start_time_ = time();
				phase_ = 1;
				if (restaurant_->tables_->EnoughFreeSeats() == false || restaurant_->manager_->Free() == false || restaurant_->tables_->QueueSize() > 1)
				{
					active = false;
				}
			}

		}
		break;
		case 1:
			{
				cerr << "\n--> Faza 1: Poczatek obslugi przez managera";
				restaurant_->tables_->TakeToManager(time());
				queue_for_tables_end_time_ = time();
				restaurant_->manager_->Reservation();
				activate(time() + 30);
				phase_ = 2;
				active = false;
			}
			break;
		case 2:
			{
				cerr << "\n--> Faza 2: Koniec obslugi przez managera";
				restaurant_->manager_->EndReservation();
				restaurant_->tables_->AddToTables(this);
				pending_processes_start_time_ = time();
				restaurant_->tables_->WakeUpQueueForTables(restaurant_->manager_->Free(),time());
				phase_ = 3;
				if(restaurant_->waiters_->Free()==false)
				{
					active = false;
				}
			}
			break;
		case 3:
			{
				cerr << "\n--> Faza 3: Kelner podaje napoj";
				restaurant_->waiters_->Reservation();
				pending_processes_end_time_ = time();
				restaurant_->tables_->RemovePendingProcess();
				activate(time() + ExponentialDistributionGenerator(900));
				phase_ = 4;
				active = false;
			}
			break;
		case 4:
			{
				cerr << "\n--> Faza 4: Kelner podaje danie glowne";
				drink_ = true;
				activate(time() + ExponentialDistributionGenerator(2500));
				phase_ = 5;
				active = false;
			}
			break;
		case 5:
			{
				cerr << "\n--> Faza 5: Rozpoczecie konsumpcji";
				dish_ = true;
				restaurant_->waiters_->EndReservation();
				restaurant_->tables_->WakeUpPendingProcessQueue(time());
				activate(time() + ExponentialDistributionGenerator(1900));
				phase_ = 6;
				active = false;
			}
			break;
		case 6:
			{
				cerr << "\n--> Faza 6: Koniec konsumpcji";
				restaurant_->tables_->RemoveFromTables(this);
				restaurant_->cash_->AddCustomerToQueue(this, time());
				restaurant_->tables_->WakeUpQueueForTables(restaurant_->manager_->Free(), time());
				phase_ = 7;
				if(restaurant_->cash_->Free()==false)
				{
					active = false;
				}
			}
			break;
		case 7:
			{
				cerr << "\n--> Faza 7: Rozpoczecie obslugi przy kasie";
				restaurant_->cash_->AddCustomerToCash(time());
				activate(time() + ExponentialDistributionGenerator(900));
				phase_ = 8;
				active = false;
			}
			break;
		case 8:
			{
				cerr << "\n--> Faza 8: Koniec obslugi przy kasie";
				restaurant_->cash_->RemoveCustomer(this);
				restaurant_->cash_->WakeUpIfPossible(time());
				SaveData();
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
				restaurant_->buffet_->ReturnCustomer(id_);
				restaurant_->cash_->AddCustomerToQueue(this,time());
				restaurant_->buffet_->WakeUpIfPossible(time());
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
	restaurant_->tables_->TableInfo();
	restaurant_->waiters_->WaitersInfo();
	restaurant_->cash_->CashInfo();
}

double Customer::NormalDistributionGenerator(const pair<const int, const int> p)
{
	static default_random_engine generator(seed_);
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}

double Customer::ExponentialDistributionGenerator(const int average)
{
	static default_random_engine generator(seed_);
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}

void Customer::SaveData()
{
	if (queue_for_tables_end_time_ > -1 && queue_for_tables_start_time_ > -1)
	{
		ofstream a_output("punkt_a.txt", ios::app);
		a_output << queue_for_tables_end_time_ - queue_for_tables_start_time_ << endl;
		a_output.close();
	}
	if (pending_processes_start_time_ != -1 && pending_processes_end_time_ != -1)
	{
		ofstream c_output("punkt_c.txt", ios::app);
		c_output << pending_processes_end_time_ - pending_processes_start_time_ << endl;
		c_output.close();
	}
}
