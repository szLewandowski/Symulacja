#pragma once
#include <queue>
#include "Tables.h"
#include "Manager.h"
#include "Waiters.h"
#include "Buffet.h"
#include "Cash.h"
#include "process.h"
#include "Customer.h"
class Restaurant
{
public:
	Restaurant();
	~Restaurant();
	Tables* tables_;
	Manager* manager_;
	Waiters* waiters_;
	Buffet* buffet_;
	Cash* cash_;
	
	queue<Process*> buffet_queue_;
	queue<Process*> tables_queue_;
	queue<Process*> cash_queue_;

	//double Uniform();
	//double NormalDistributionGenerator(int average, int variance);
	//double ExponentialDistributionGenerator(int average);
	
private:
	int seed_ = 5;
};

