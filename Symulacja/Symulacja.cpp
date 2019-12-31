#include <iostream>
#include "process.h"
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
	const bool step_mode = true;
	Restaurant restaurant;
	const auto event_list = new Event_list;
	auto clock = 0.0;
	Process* current_process = new Customer(event_list);
	current_process->activate(0);
	current_process = nullptr;
	while (clock<10000)
	{
		auto current_event = event_list->RemoveFirst();
		current_process = current_event->proc_;
		clock = current_event->event_time_;
		cerr << "**************************************************\n";
		cerr << "New clock: " << clock << endl;
		current_event = nullptr;
		current_process->execute();
		if (current_process->terminated_)
			delete current_process;
		if(step_mode)
			cin.get();
	}

	return 0;
}