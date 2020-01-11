#include "Tables.h"
#include <iostream>

Tables::Tables()
{
	std::cerr << "Make Tables\n";
	for (int i = 0; i < double_seats_*2; ++i)
	{
		double_tables_[0][i] = 0;
	}
	for (int i = 0; i < triple_seats_*3; ++i)
	{
		triple_tables_[0][i] = 0;
	}
	for (int i = 0; i < quadruple_seats_*4; ++i)
	{
		quadruple_tables_[0][i] = 0;
	}
}

Tables::~Tables()
{
	std::cerr << "Delete Tables\n";
}

void Tables::TableInfo()
{
	cout << "\n\nTable info:\n";
	cout << "Kolejka do stolikow: " << queue_.size() << endl;
	cout << "Procesy oczekujace na kelnera: " << pending_processes_.size() << endl;
	int free_2 = 0;
	int free_3 = 0;
	int free_4 = 0;
	for (int i = 0; i < double_seats_; ++i)
	{
		if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
			++free_2;
	}
	for (int i = 0; i < triple_seats_; ++i)
	{
		if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2] == 0)
			++free_3;
	}
	for (int i = 0; i < quadruple_seats_; ++i)
	{
		if (quadruple_tables_[i][0] == 0 && quadruple_tables_[i][1] == 0 && quadruple_tables_[i][2] == 0 && quadruple_tables_[i][3] == 0)
			++free_4;
	}
	cout << "Zajete stoliki:\n";
	cout << "Dwuosobowe: " << double_seats_ - free_2 << "/" << double_seats_ << endl;
	cout << "Trzyosobowe: " << triple_seats_ - free_3 << "/" << triple_seats_ << endl;
	cout << "Czteroosobowe: " << quadruple_seats_ - free_4 << "/" << quadruple_seats_ << endl;	
}

void Tables::AddToQueue(Process* customer)
{
	queue_.push(customer);
}

void Tables::TakeToManager()
{
	queue_.pop();
}

void Tables::AddToTables(Process* customer)
{
	const int need = customer->group_size_;
	pending_processes_.push(customer);
	if(need==1)
	{
		for (int i = 0; i < double_seats_; ++i)
		{
			if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
			{
				double_tables_[i][0] = customer->id_;
				return;
			}
		}
		for (int i = 0; i < triple_seats_; ++i)
		{
			if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2] == 0)
			{
				triple_tables_[i][0] = customer->id_;
				return;
			}
		}
		for (int i = 0; i < quadruple_seats_; ++i)
		{
			if (quadruple_tables_[i][0] == 0 && quadruple_tables_[i][1] == 0 && quadruple_tables_[i][2] == 0 && quadruple_tables_[i][3] == 0)
			{
				quadruple_tables_[i][0] = customer->id_;
				return;
			}
		}
		cerr << "ERROR Tables.cpp/AddToTables: There is no free seats!\n";
		cin.get();
	}
	else if(need==2)
	{
		for (int i = 0; i < double_seats_; ++i)
		{
			if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
			{
				double_tables_[i][0] = customer->id_;
				double_tables_[i][1] = customer->id_;
				return;
			}
		}
		for (int i = 0; i < triple_seats_; ++i)
		{
			if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2] == 0)
			{
				triple_tables_[i][0] = customer->id_;
				triple_tables_[i][1] = customer->id_;
				return;
			}
		}
		for (int i = 0; i < quadruple_seats_; ++i)
		{
			if (quadruple_tables_[i][0] == 0 && quadruple_tables_[i][1] == 0 && quadruple_tables_[i][2] == 0 && quadruple_tables_[i][3] == 0)
			{
				quadruple_tables_[i][0] = customer->id_;
				quadruple_tables_[i][1] = customer->id_;
				return;
			}
		}
		cerr << "ERROR Tables.cpp/AddToTables: There is no free seats!\n";
		cin.get();
	}
	else if(need==3)
	{
		for (int i = 0; i < triple_seats_; ++i)
		{
			if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2] == 0)
			{
				triple_tables_[i][0] = customer->id_;
				triple_tables_[i][1] = customer->id_;
				triple_tables_[i][2] = customer->id_;
				return;
			}
		}
		for (int i = 0; i < quadruple_seats_; ++i)
		{
			if (quadruple_tables_[i][0] == 0 && quadruple_tables_[i][1] == 0 && quadruple_tables_[i][2] == 0 && quadruple_tables_[i][3] == 0)
			{
				quadruple_tables_[i][0] = customer->id_;
				quadruple_tables_[i][1] = customer->id_;
				quadruple_tables_[i][2] = customer->id_;
				return;
			}
		}
		int first = double_seats_, second = double_seats_;
		for (int i = 0; i < double_seats_; ++i)
		{
			if (first == double_seats_)
			{
				if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
				{
					first = i;
					continue;
				}
			}
			if (first < double_seats_ && second == double_seats_)
			{
				if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
				{
					second = i;
				}
			}
		}
		if (first < double_seats_ && second < double_seats_)
		{
			double_tables_[first][0] = customer->id_;
			double_tables_[first][1] = customer->id_;
			double_tables_[second][0] = customer->id_;
			return;
		}
		cerr << "ERROR Tables.cpp/AddToTables: There is no free seats!\n";
		cin.get();
	}
	else
	{
		for (int i = 0; i < quadruple_seats_; ++i)
		{
			if (quadruple_tables_[i][0] == 0 && quadruple_tables_[i][1] == 0 && quadruple_tables_[i][2] == 0 && quadruple_tables_[i][3] == 0)
			{
				quadruple_tables_[i][0] = customer->id_;
				quadruple_tables_[i][1] = customer->id_;
				quadruple_tables_[i][2] = customer->id_;
				quadruple_tables_[i][3] = customer->id_;
				return;
			}
		}
		int first_2 = double_seats_, second_2 = double_seats_;
		for (int i = 0; i < double_seats_; ++i)
		{
			if (first_2 == double_seats_)
			{
				if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
				{
					first_2 = i;
					continue;
				}
			}
			if (first_2 < double_seats_ && second_2 == double_seats_)
			{
				if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
				{
					second_2 = i;
				}
			}
		}
		int first_3 = triple_seats_, second_3 = triple_seats_;
		for (int i = 0; i < triple_seats_; ++i)
		{
			if (first_3 == triple_seats_)
			{
				if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2] == 0)
				{
					first_3 = i;
					continue;
				}
			}
			if (first_3 < triple_seats_ && second_3 == triple_seats_)
			{
				if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2] == 0)
				{
					second_3 = i;
				}
			}
		}
		if (first_2 < double_seats_ && second_2 < double_seats_)
		{
			double_tables_[first_2][0] = customer->id_;
			double_tables_[first_2][1] = customer->id_;
			double_tables_[second_2][0] = customer->id_;
			double_tables_[second_2][1] = customer->id_;
			return;
		}
		if (first_2 < double_seats_ && first_3 < triple_seats_)
		{
			double_tables_[first_2][0] = customer->id_;
			double_tables_[first_2][1] = customer->id_;
			triple_tables_[first_3][0] = customer->id_;
			triple_tables_[first_3][1] = customer->id_;
			return;
		}
		if(first_3<triple_seats_ && second_3<triple_seats_)
		{
			triple_tables_[first_3][0] = customer->id_;
			triple_tables_[first_3][1] = customer->id_;
			triple_tables_[first_3][2] = customer->id_;
			triple_tables_[second_3][0] = customer->id_;
			return;
		}
		cerr << "ERROR Tables.cpp/AddToTables: There is no free seats!\n";
		cin.get();
	}

}

void Tables::RemoveFromTables(Process* process)
{
	for (int i = 0; i < double_seats_ * 2; ++i)
	{
		if (double_tables_[0][i] == process->id_)
		{
			double_tables_[0][i] = 0;
		}

	}
	for (int i = 0; i < triple_seats_ * 3; ++i)
	{
		if (triple_tables_[0][i] == process->id_)
		{
			triple_tables_[0][i] = 0;
		}

	}
	for (int i = 0; i < quadruple_seats_ * 4; ++i)
	{
		if (quadruple_tables_[0][i] == process->id_)
		{
			quadruple_tables_[0][i] = 0;
		}

	}
}

bool Tables::EnoughFreeSeats()
{
	const int need = queue_.front()->group_size_;
	int free_2 = 0;
	int free_3 = 0;
	int free_4 = 0;
	for (int i = 0; i < double_seats_; ++i)
	{
		if (double_tables_[i][0] == 0 && double_tables_[i][1] == 0)
			++free_2;
	}
	for (int i = 0; i < triple_seats_; ++i)
	{
		if (triple_tables_[i][0] == 0 && triple_tables_[i][1] == 0 && triple_tables_[i][2]==0)
			++free_3;
	}
	for (int i = 0; i < quadruple_seats_; ++i)
	{
		if (quadruple_tables_[i][0] == 0 && quadruple_tables_[i][1] == 0 && quadruple_tables_[i][2] == 0 && quadruple_tables_[i][3] == 0)
			++free_4;
	}
	if (need < 3)
	{
		if (free_2 != 0 || free_3 != 0 || free_4 != 0)
		{
			return true;
		}
	}
	else if (need == 3)
	{
		if (free_3 != 0 || free_4 != 0 || free_2 > 1)
		{
			return true;
		}
	}
	else
	{
		if (free_4 != 0 || free_2 > 1 || free_3 > 1 || (free_2 > 0 && free_3 > 0))
		{
			return true;
		}
	}
	return false;
}

int Tables::QueueSize() const
{
	return static_cast<int>(queue_.size());
}

void Tables::WakeUpQueueForTables(const bool manager_free, const double new_time)
{
	if(QueueSize() && EnoughFreeSeats() && manager_free )
	{
		queue_.front()->execute(new_time);
	}
}

void Tables::WakeUpPendingProcessQueue(const double new_time)
{
	if(pending_processes_.empty()==false)
	{
		pending_processes_.front()->execute(new_time);
	}
}

void Tables::WaitersService()
{
	pending_processes_.pop();
}

void Tables::RemovePendingProcess()
{
	pending_processes_.pop();
}

void Tables::Alarm()
{
	if (queue_.empty() == false)
	{
		for (int i = 0; i < static_cast<int>(queue_.size()); ++i)
		{
			Process* temp = queue_.front();
			queue_.pop();
			if (rand() % 10 < 3)
			{
				delete temp;
			}
			else
			{
				queue_.push(temp);
			}
		}
	}
	if (pending_processes_.empty() == false)
	{
		for (int i = 0; i < static_cast<int>(pending_processes_.size()); ++i)
		{
			Process* temp = pending_processes_.front();
			pending_processes_.pop();
			if (rand() % 10 < 3)
			{
				RemoveFromTables(temp);
				delete temp;
			}
			else
			{
				pending_processes_.push(temp);
			}
		}
	}
}

void Tables::Cleaning(vector<int>* id)
{
	for (auto it = id->begin(); it != id->end(); ++it)
	{
		for (int i = 0; i < double_seats_ * 2; ++i)
		{
			if (double_tables_[0][i] == *it)
			{
				double_tables_[0][i] = 0;
			}
		}
		for (int i = 0; i < triple_seats_ * 3; ++i)
		{
			if (triple_tables_[0][i] == *it)
			{
				triple_tables_[0][i] = 0;
			}
		}
		for (int i = 0; i < quadruple_seats_ * 4; ++i)
		{
			if (quadruple_tables_[0][i] == *it)
			{
				quadruple_tables_[0][i] = 0;
			}
		}
	}
}
