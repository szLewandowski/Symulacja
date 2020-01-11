#pragma once
#include "process.h"

class Tables
{
public:
	Tables();
	~Tables();
	void TableInfo();
	void AddToQueue(Process*);
	void TakeToManager();
	void AddToTables(Process*);
	void RemoveFromTables(Process*);
	bool EnoughFreeSeats();
	int QueueSize() const;
	void WakeUpQueueForTables(bool, double);
	void WakeUpPendingProcessQueue(double);
	void WaitersService();
	void RemovePendingProcess();
	void Alarm();
	void Cleaning(vector<int>*);
private:
	queue<Process*> queue_;
	queue<Process*> pending_processes_;
	const static int double_seats_ = 4;
	const static int  triple_seats_ = 10;
	const static int quadruple_seats_ = 4;
	double double_tables_[double_seats_][2]{};
	double triple_tables_[triple_seats_][3]{};
	double quadruple_tables_[quadruple_seats_][4]{};
};

