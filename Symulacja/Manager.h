#pragma once


class Manager
{
public:
	Manager();
	~Manager();
	bool Free() const;
	void Reservation();
	void EndReservation();
private:
	bool is_free_;
};

