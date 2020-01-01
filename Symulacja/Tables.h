#pragma once
#include "process.h"

class Tables
{
public:
	Tables();
	~Tables();
	void AddToQueue(Process*);
private:
	queue<Process*> queue_;
};

