#pragma once
#include "process.h"
#include "Event_list.h"
using namespace std;
class Customer :
	public Process
{
public:
	explicit Customer(Event_list*);
	void execute() override;	
};

