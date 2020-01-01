#include "Tables.h"
#include <iostream>

Tables::Tables()
{
	std::cerr << "Make Tables\n";
}

Tables::~Tables()
{
	std::cerr << "Delete Tables\n";
}

void Tables::AddToQueue(Process* customer)
{
	queue_.push(customer);
}
