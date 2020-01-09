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

int Event_list::AlarmDecimation(vector<int>* id, bool& manager)
{
    int waiters_free = 0;
    if (first_ == nullptr)
	{
    	//List empty
        cerr << "Event list is empty\n";
	}
    else if(first_!=nullptr && first_==last_)
    {
    	//single element list
        if (rand() % 10 < 3 && first_->proc_->phase_ != 0)
	    {
            id->push_back(first_->proc_->id_);
            if (first_->proc_->phase_ == 4 || first_->proc_->phase_ == 5)
            {
                waiters_free++;
            }
            if (first_->proc_->phase_ == 2)manager = true;
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
            if (rand() % 10 < 3 && temp->proc_->phase_ != 0)
            {
                if (first_ == last_)
            	{
                    id->push_back(temp->proc_->id_);
                    if (temp->proc_->phase_ == 4 || temp->proc_->phase_ == 5)
                    {
                        waiters_free++;
                    }
                    if (temp->proc_->phase_ == 2)manager = true;
                    delete temp->proc_;
                    first_ = last_ = nullptr;
            		return waiters_free;
            	}
                first_->next_->prev_ = nullptr;
                first_ = first_->next_;
                id->push_back(temp->proc_->id_);
                if (temp->proc_->phase_ == 4 || temp->proc_->phase_ == 5)
                {
                    waiters_free++;
                }
                if (temp->proc_->phase_ == 2)manager = true;
                delete temp->proc_;
            }
            else
            {
                if (temp != last_) 
                {
                    temp = first_->next_;
                    break;
                }
                return waiters_free;
            }
        }
    	//removing rest elements
        while (true)
        {
            if (rand() % 10 < 3 && temp->proc_->phase_ != 0)
            {
                if (temp == last_)
                {
                    temp->prev_->next_ = nullptr;
                    last_ = temp->prev_;
                    id->push_back(temp->proc_->id_);
                    if (temp->proc_->phase_ == 4 || temp->proc_->phase_ == 5)
                    {
                        waiters_free++;
                    }
                    if (temp->proc_->phase_ == 2)manager = true;
                    delete temp->proc_;
                    return waiters_free;
                }
                temp->prev_->next_ = temp->next_;
                temp->next_->prev_ = temp->prev_;
                Event* help = temp->next_;
                id->push_back(temp->proc_->id_);
                if (temp->proc_->phase_ == 4 || temp->proc_->phase_ == 5)
                {
                    waiters_free++;
                }
                if (temp->proc_->phase_ == 2)manager = true;
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
                else return waiters_free;
            }
        }
    }
    return waiters_free;
}

double Event_list::FirstEventTime()
{
	if(first_!=nullptr)
		return first_->event_time_;
    return -1;
}

void Event_list::TestingFunction() const
{
    cout << "Event_list: Testing function:\n";
    if (first_ == nullptr || first_ == last_)
    {
        cout << "Nothing to test :(\n";
    }
    else
    {
        Event* temp = first_;
        while (temp != nullptr)       //a bit risky, consider (temp!=last_) with extra cout
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
