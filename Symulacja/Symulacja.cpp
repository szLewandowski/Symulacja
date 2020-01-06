#include <iostream>
#include "Restaurant.h"
#include <random>
#include "Event_list.h"
#include "Customer.h"
using namespace std;

double NormalDistributionGenerator(const pair<const int, const int> p) {
	static default_random_engine generator;
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}
double ExponentialDistributionGenerator(const int average) {
	static default_random_engine generator;
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}

int main()
{
	const bool step_mode = false;
	Restaurant* restaurant = new Restaurant;
	const auto event_list = new Event_list;
	auto clock = 0.0;
	Process* current_process = new Customer(event_list,restaurant,0);
	current_process->activate(0);
	current_process = nullptr;
	
	double prev_clock = -1;
	int terminated_counter = 0;
	int highest_id = 0;
	
	while (clock < 1000000)
	{		
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
		if (current_process->id_ > highest_id)
		{
			highest_id = current_process->id_;
		}
		prev_clock = clock;
	}
	cout << "\nProcesses created: " << highest_id << endl;
	cout << "Processes deleted: " << terminated_counter << endl;

	return 0;
}