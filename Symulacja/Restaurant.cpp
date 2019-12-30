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




/*
 *
//Generatory:
double Restaurant::Uniform()
{
    const auto a = 16807;
    double const range = 2147483647;
    const auto q = 127773;
    const auto r = 2836;

    const auto h = seed_ / q;
    seed_ = a * (seed_ - q * h) - r * h;
    if (seed_ < 0) seed_ += range;
    const auto val = static_cast<double>(seed_) / range;
    return val;

}
double Restaurant::NormalDistributionGenerator(const int average, const int variance)
{
    auto y = 0;
    const auto n = 12;
    for (auto i = 0; i < n; i++)
    {
        y += Uniform();
    }
    return int(((y - (double(n) / 2)) * (variance * 12 / n)) + average);
}
double Restaurant::ExponentialDistributionGenerator(const int average)
{
    const auto k = log(Uniform());
    double val = ((-1) * (k)) * average;
    return int(val);
}

*/