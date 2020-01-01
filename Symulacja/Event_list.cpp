#include "Event_list.h"
#include <iostream>
#include "process.h"    //used for avoid warnings
using namespace std;

void Event_list::AddNewEvent(Event* add_event)
{
    if (first_ == nullptr) //If list is empty add event on first
    {
        first_ = last_ = add_event;
    }
    else if (add_event->event_time_ <= first_->event_time_) //Add event on beginning
    {
        first_->prev_ = add_event;
        add_event->next_ = first_;
        first_ = add_event;
    }
    else if (add_event->event_time_ >= last_->event_time_) //Add event on end
    {
        add_event->prev_ = last_;
        last_->next_ = add_event;
        last_ = add_event;
    }
    else {

        Event* search = first_;
        while (search->event_time_ <= add_event->event_time_)
        {
            search = search->next_;
        }
        add_event->next_ = search;
        add_event->prev_ = search->prev_;
        search->prev_->next_ = add_event;
        search->prev_ = add_event;
        search = nullptr;
    }
}

/*
void Event_list::DeleteEvent(int id)
{
    if (first_->GetId() == id)
    {
        if (first_ == last_)
        {
            Event* event_to_delete = first_;
            first_ = last_ = nullptr;
            delete event_to_delete;
            return;
        }
        else
        {
            Event* event_to_delete = first_;
            first_ = first_->next_;
            first_->prev_ = nullptr;
            delete event_to_delete;
            return;
        }
    }
    if (last_->GetId() == id)
    {
        Event* event_to_delete = last_;
        last_ = last_->prev_;
        last_->next_ = NULL;
        delete event_to_delete;
        return;
    }
    bool found = true;
    Event* search = first_;
    cout << search << endl;
    search->ShowParameter();
    while (search->GetId() != id)
    {
        if (search->next_ == nullptr)
        {
            found = false;
            break;
        }
        search = search->next_;
    }
    if (found == true)
    {
        search->next_->prev_ = search->prev_;
        search->prev_->next_ = search->next_;
        delete search;
    }

}
*/

void Event_list::AlarmDecimation()
{
    if (first_ == nullptr)
	{
    	//List empty
        cerr << "Event list is empty\n";
	}
    else if(first_!=nullptr && first_==last_)
    {
    	//single element list
        if (rand() % 10 < 3)
	    {
            delete first_->proc_;
            first_ = last_ = nullptr;
            cerr << "Event List - one client removed\n";
	    }
    }
    else
    {
        Event* temp;
    	//removing first elements
        while (true) {
            temp = first_;
            if (rand() % 10 < 3)
            {
            	if(first_==last_)
            	{
                    delete temp->proc_;
                    first_ = last_ = nullptr;
            		return;
            	}
                first_->next_->prev_ = nullptr;
                first_ = first_->next_;
                delete temp->proc_;
            }
            else
            {
                if (temp != last_) {
                    temp = first_->next_;
                    break;
                }
                else return;
            }
        }
    	//removing rest elements
        while (true)
        {
            if (rand() % 10 < 3)
            {
                if (temp == last_)
                {
                    temp->prev_->next_ = nullptr;
                    last_ = temp->prev_;
                    delete temp->proc_;
                    return;
                }
                temp->prev_->next_ = temp->next_;
                temp->next_->prev_ = temp->prev_;
                Event* help = temp->next_;
                delete temp->proc_;
                temp = help;
                help = nullptr;
            }
            else
            {
                if (temp != last_)
                {
                    temp = temp->next_;
                }
                else return;
            }
        }
    }
}

double Event_list::FirstEventTime()
{
	if(first_!=nullptr)
		return first_->event_time_;
    return -1;
}

void Event_list::TestingFunction()
{
    cout << "Event_list: Testing function:\n";
	if(first_==nullptr || first_==last_)
	{
        cout << "Nothing to test :(\n";
	}
    else
    {
        Event* temp = first_;
        while (temp!=nullptr)       //a bit risky, consider (temp!=last_) with extra cout
        {
            cout << temp->event_time_ << "  ";
            temp = temp->next_;
        }
    }
    cin.get();
}

Event* Event_list::RemoveFirst()
{
    if (first_ != nullptr) {
        Event* first_event_from_list = first_;
        first_ = first_->next_;
        first_event_from_list->next_ = nullptr;
        first_event_from_list->prev_ = nullptr;
        return first_event_from_list;
    }
    cerr << "ERROR Event_list: There is no event to remove!\n";
    cin.get();
    return nullptr;
}
