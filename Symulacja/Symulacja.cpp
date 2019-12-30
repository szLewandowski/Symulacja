#include <iostream>
#include "process.h"
#include "Restaurant.h"
#include <random>
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
	Process* current;
	auto clock = 0.0;


	while(clock < 100)
	{
		// pêtla g³ówna symulacji

		
		clock++;
	}
	
	return 0;
}