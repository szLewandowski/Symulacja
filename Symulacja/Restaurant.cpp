#include "Restaurant.h"
#include <iostream>

Restaurant::Restaurant()
{
	tables_ = new Tables;
	manager_ = new Manager;
	waiters_ = new Waiters;
	buffet_ = new Buffet;
	cash_ = new Cash;
}

Restaurant::~Restaurant()
{
	delete tables_;
	tables_ = nullptr;
	delete manager_;
	manager_ = nullptr;
	delete waiters_;
	waiters_ = nullptr;
	delete buffet_;
	buffet_ = nullptr;
	delete cash_;
	cash_ = nullptr;
}
