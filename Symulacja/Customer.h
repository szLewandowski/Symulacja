#pragma once
#include "process.h"
#include "Event_list.h"
#include "Restaurant.h"
using namespace std;
class Customer :
	public Process
{
public:
	explicit Customer(Event_list*,Restaurant*,int);
	void execute(double) override;
	Restaurant* restaurant_;
	static const int seed_ = 8599765;
	static double NormalDistributionGenerator(pair<const int, const int> p);
	static double ExponentialDistributionGenerator(int average);
	double queue_for_tables_start_time_ = -1;
	double queue_for_tables_end_time_ = -1;
	double pending_processes_start_time_ = -1;
	double pending_processes_end_time_ = -1;
	void SaveData();
	bool drink_ = false;
	bool dish_ = false;
};