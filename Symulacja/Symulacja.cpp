#include <iostream>
#include "Restaurant.h"
#include <random>
#include "Event_list.h"
#include "Customer.h"
using namespace std;

const int kSeed = 123456;
double NormalDistributionGenerator(const pair<const int, const int> p) {
	static default_random_engine generator(kSeed);
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}
double ExponentialDistributionGenerator(const int average) {
	static default_random_engine generator(kSeed);
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}
bool AreSame(const double a, const double b)
{
	return fabs(a - b) < DBL_EPSILON;
}
int main()
{
	const bool step_mode = false;
	Restaurant* restaurant = new Restaurant;
	const auto event_list = new Event_list;
	auto clock = 0.0;
	Process* current_process = new Customer(event_list, restaurant, 0);
	current_process->activate(0);
	current_process = nullptr;
	
	double prev_clock = -1;
	int terminated_counter = 0;
	int highest_id = 0;

	const pair<int, int> alarm_distribution = make_pair(12200, 50);
	double alarm_time = NormalDistributionGenerator(alarm_distribution);
	
	while (clock < 300000)
	{
		if (event_list->FirstEventTime() > alarm_time)
		{
			clock = alarm_time;
			cerr << "\n************************************************************************************\n";
			cerr << "\t\tALARM";
			cerr << "\n************************************************************************************\n";
			//event_list->TestingFunction();
			cout << "Event list: \n";
			vector<int>* deleted = new vector<int>;
			bool manager = false;
			int waiters_free = event_list->AlarmDecimation(deleted, manager);
			cout << "Event list: " << deleted->size() << endl;
			//event_list->TestingFunction();
			restaurant->Alarm(deleted, waiters_free, manager);
			alarm_time += NormalDistributionGenerator(alarm_distribution);
			cerr << "NEW ALARM WILL BE: " << alarm_time << endl;
			prev_clock = clock;
			if (manager)cout << "Manager free!\n";
			restaurant->buffet_->BuffetInfo();
			restaurant->tables_->TableInfo();
			restaurant->waiters_->WaitersInfo();
			restaurant->cash_->CashInfo();
			restaurant->WakeUp(clock);
			cerr << "\n************************************************************************************\n";
			continue;
		}		
		auto current_event = event_list->RemoveFirst();
		current_process = current_event->proc_;
		clock = current_event->event_time_;
		cerr << "\n**************************************************\n";
		cerr << "Current clock: " << clock << endl;
		current_event = nullptr;
		current_process->execute(clock);

		if (prev_clock >= clock)
		{
			cerr << "ERROR! TIME TRAVEL!\n";
			cin.get();
		}
		if (current_process->id_ > highest_id)
		{
			highest_id = current_process->id_;
		}
		if (current_process->terminated_)
		{
			cout << "\nPROCES TERMINATED!\n";
			terminated_counter++;
			delete current_process;
		}
		if (step_mode)
		{
			cin.get();
		}

		prev_clock = clock;		
	}
	cout << "\nProcesses created: " << highest_id << endl;
	cout << "Processes deleted: " << terminated_counter << endl;

	return 0;
}