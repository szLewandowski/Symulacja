#include "Customer.h"
#include <iostream>

Customer::Customer(Event_list* list): Process(list)
{
	//cerr << "Customer constructor\n";
}

void Customer::execute()
{
	auto active = true;
	while(active)
	{
		switch(phase_)
		{
		case 0:
			cerr << "Pojawienie sie nowej grupy klientow";
			break;
		case 1:
			cerr << "Poczatek obslugi przez managera";
			break;
		case 2:
			cerr << "Koniec obslugi przez managera";
			break;
		case 3:
			cerr << "Kelner podaje napoj";
			break;
		case 4:
			cerr << "Kelner podaje danie glowne";
			break;
		case 5:
			cerr << "Rozpoczecie konsumpcji";
			break;
		case 6:
			cerr << "Koniec konsumpcji";
			break;
		case 7:
			cerr << "Rozpoczecie obslugi przy kasie";
			break;
		case 8:
			cerr << "Koniec obslugi przy kasie";
			break;
		case 9:
			cerr << "Poczatek obslugi w bufecie";
			break;
		case 10:
			cerr << "Koniec obslugi w bufecie";
			break;			
		}
	}
}
