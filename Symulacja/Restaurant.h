#pragma once
#include "Tables.h"
#include "Manager.h"
#include "Waiters.h"
#include "Buffet.h"
#include "Cash.h"

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
	
	void hello()
	{
		cout << "Hello Restaurant!\n";
		cin.get();
	}
	
	//double Uniform();
	//double NormalDistributionGenerator(int average, int variance);
	//double ExponentialDistributionGenerator(int average);
	
private:
	//int seed_ = 5;
};

