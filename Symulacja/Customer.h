#pragma once
#include "process.h"
using namespace std;
class Customer :
	public Process
{
public:
	void execute() override;
	
};

