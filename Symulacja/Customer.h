#pragma once
#include "process.h"
#include "Event_list.h"
#include "Restaurant.h"
using namespace std;
class Customer :
	public Process
{
public:
	explicit Customer(Event_list*,Restaurant*);
	void execute() override;
	Restaurant* restaurant_;
	static double NormalDistributionGenerator(const pair<const int, const int> p);
	static double ExponentialDistributionGenerator(const int average);
	
};