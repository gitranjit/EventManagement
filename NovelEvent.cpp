#include "NovelEvent.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

float fmax(float a,float b){
    if(a>b) return a;
    return b;
}

vector<Event *> ManagementSystem::eventList;

Date::Date() {
  day = 0;
  month = 0;
  year = 0;
}

Date::Date(int day, int month, int year) {
  this->day = day;
  this->month = month;
  this->year = year;
}

void Date::set_date() {
  int d, m, y;
  cout << "Enter the day: ";
  cin >> d;
  cout << "Enter the month: ";
  cin >> m;
  cout << "Enter the year: ";
  cin >> y;

  if (d > 0 && d <= 31 && m > 0 && m <= 12 && y > 0) {
    day = d;
    month = m;
    year = y;
  } else {
    cout << "Invalid date, please enter input again" << endl;
    set_date();
  }
}

void Date::setNew_date() {
  cout << "Enter New Details" << endl;
  set_date();
}

int Date::get_day() { return day; }

int Date::get_month() { return month; }

int Date::get_year() { return year; }

Guests::Guests() {
  name = "";
  mobile_number = "";
}

Guests::Guests(string name, string mobile_number) {
  this->name = name;
  this->mobile_number = mobile_number;
}

void Guests::setGuests() {
  cout << "Enter the name: ";
  cin.ignore();
  getline(cin, name);
  cout << "Enter the mobile number: ";
  cin.ignore();
  getline(cin, mobile_number);
}

string Guests::getGuestsName() { return name; }

string Guests::getGuestsMob() { return mobile_number; }

int Event::eventCount = 0;

Event::Event() {
  eventCount++;
  eventId = eventCount;
}

// setEventName() function

void Event::setEventName() {

  cout << "Enter the Event name: ";
  cin.ignore();
  getline(cin, nameOfEvent);
}

// setNewEventName function

void Event::setNewEventName() {
  // eventCount++;
  cout << "Enter the new Event name: ";
  cin.ignore();
  getline(cin, nameOfEvent);
}

string Event::getEventName() { return nameOfEvent; }

// setNoofGuests function

void Event::setNoOfGuests() {
  cout << "Enter the number of guests: ";
  cin >> noOfGuests;
}

int Event::getNoOfGuests() { return noOfGuests; }

// addGuest function

Guests guest;
void Event::add_guest() {
  for (int i = 1; i <= noOfGuests; i++) {
    guest.setGuests();
  }
}

// setFood function

void Event::setFood() {
  cout << "Enter breakfast count: ";
  cin >> breakfast_count;
  cout << "Enter tea count: ";
  cin >> tea_count;
  cout << "Enter meal count: ";
  cin >> meal_count;

  if (breakfast_count < 0 || tea_count < 0 || meal_count < 0) {
    cout << "enter correct details" << endl;
    setFood();
  }
}

// calculate_cost function

void Event::calculate_cost() {
      setFood();
  if (breakfast_count >= breakfastLim) {
    remained_cost += (breakfast_count - breakfastLim) * 50;
  }

  if (tea_count >= teaLim) {
    remained_cost += (tea_count - teaLim) * 10;
  }

  if (meal_count >= mealLim) {
    remained_cost += (meal_count - mealLim) * 100;
  }

  
}

// generate invitations function

void Event::generate_invitation() {
  cout << "-------------------------------------------------";
  cout << "You are invited to " << getEventName() << " on "
       << eventDate.get_day() << "/" << eventDate.get_month() << "/"
       << eventDate.get_year();
  cout << "---------------------------------------------------";
}

// advance_payment function

void Event::pending_payment(){
    bool visitLoop=0;
    int eventPendingId;
    cout << "Enter Id of event to complete pending payment: ";
    cin>>eventPendingId;

    for(int i=0;i<ManagementSystem::eventList.size();i++){
        if(eventPendingId==ManagementSystem::eventList[i]->eventId){

            ManagementSystem::eventList[i]->advance_payment();
            
            visitLoop=1;
        }
    }

    if(visitLoop==0){
        cout<<"No event found with this id"<<endl;
    }
}


void Event::advance_payment() {
    if(status>=1){
        cout<<"Event is already paid"<<endl;
        return;
    }
  advanceCost = cost * 0.5;
  cout << "You have to pay " << advanceCost << " as advance" << endl;

  int statusInput;
  cout << "enter 1 to pay now and 0 to keep event pending: ";
  cin >> statusInput;

  if (statusInput == 1) {
    cout << "You have paid " << advanceCost << " now" << endl;
    status = 1;
    remained_cost -= advanceCost;
  } else {
    cout << "Your Event is pending" << endl;
  }
}

// cancellationCharges fucntion

void Event::cancellationCharges(int tempStatus) {

  // calculate_cost();         // may be not required
  // ******************************

  cout << "The advance cost you paid will be refunded but you have to pay "
          "some cancellation charges"
       << endl;

    if(tempStatus==1){
        if(cost * 0.3 < 15000){
            cout <<"You have to pay " << fmax(float(0),(cost * 0.3)-advance) << " now as cancellation charges" << endl;
        }
        else{
            cout << "You have to pay " << fmax(15000 - advance,float(0)) << " now as cancellation charges" << endl;
        }
    }
    
  if (cost * 0.3 < 15000) {
    cout << "You have to pay " << cost * 0.3 << " now as cancellation charges"
         << endl;
  } else {
    cout << "You have to pay 15000 now as cancellation charges" << endl;
  }
  cout << "Booking cancelled" << endl;
  status = -1; // event marked as cancelled
}

// getCost function

float Event::getCost() { return cost; }

// setEventDate function

void Event::setEventDate() { eventDate.set_date(); }

// setNewEventDate function

void Event::setNewEventDate() { eventDate.setNew_date(); }

void Event:: bookHotel(){
    cout << "Enter the number of hotel rooms required: ";
    cin >> hotelRooms;
    cost += 500 * hotelRooms;
    remained_cost = cost;
}

void Event::final_payment() {
    
    
    int eventPayId=0;
    cout << "Enter Id of event to complete the payment process: ";
    cin>>eventPayId;
  
    
    bool visitLoop=0;
    

    for(int i=0;i<ManagementSystem::eventList.size();i++) {
        if(ManagementSystem::eventList[i]->eventId == eventPayId){
            int currStatus = ManagementSystem::eventList[i]->status;
            if(currStatus!=1){
                if(currStatus==0) cout << "Your payment is pending" << endl;
                else if(currStatus==2) cout << "Your payment is already done" << endl;

                return;
            }
            calculate_cost();
            cout << "You have to pay " << remained_cost << " now" << endl;
            
            cout << "payment done";
            this->status = 2;   // check for error
            remained_cost = 0;
            visitLoop=1;
        }
    }

    if(visitLoop==0) {
        cout << "Event not found" << endl;
    }
    
    
}

// 4 hrs slot class definition

shortEvent::shortEvent() {
  breakfastLim = 25;
  teaLim = 25;
  mealLim = 0;
  cost = 10000;
  remained_cost = 10000;
  advance = 5000;
  getCost();
}

// 8 hrs slot class definition

mediumEvent::mediumEvent() {
  breakfastLim = 25;
  teaLim = 25;
  mealLim = 25;
  cost = 18000;
  remained_cost = 18000;
  advance = 9000;
  getCost();
}

// 12 hrs slot class definition

longEvent::longEvent() {
  breakfastLim = 50;
  teaLim = 25;
  mealLim = 25;
  cost = 25000;
  remained_cost = 25000;
  advance = 12500;
  getCost();
}

// 24 hrs slot class definition

extraLongEvent::extraLongEvent() {
  breakfastLim = 50;
  teaLim = 25;
  mealLim = 50;
  cost = 45000;
  advance = 22500;
  remained_cost = 45000;
  getCost();
}

void ManagementSystem::storeEvent(Event *event) {
  event->setEventName();
  event->setEventDate();
  event->setNoOfGuests();
  // event->setFood();
  // event->calculate_cost();
  event->bookHotel();
  event->advance_payment();
  eventList.push_back(event);
}

void ManagementSystem::storeUpdatedEvent(Event *event, int eventUpdateId,
                                         int flag) {

  bool loopFlag = 0;

  for (int i = 0; i < eventList.size(); i++) {
    if (eventList[i]->eventId == eventUpdateId) {
      loopFlag = 1;
      if (flag == 1) {
            eventList[i]->setNewEventName();
        // eventList[i]->nameOfEvent = event->newNameOfEvent;
      }
      if (flag == 2) {
        event->setNewEventDate();
        eventList[i]->eventDate.day = event->eventDate.day;
        eventList[i]->eventDate.month = event->eventDate.month;
        eventList[i]->eventDate.year = event->eventDate.year;
      }
    }
  }
  if (loopFlag == 0) {
    cout << "Event ID not found" << endl;
  }
}

void ManagementSystem::deleteCancelledEvent() {
  cout << "These are the cancelled events Id: ";
  for (int i = 0; i < cancelledId.size(); i++) {
    cout << cancelledId[i] << "  ";
  }
  cout << endl;

  int index = -1;
  int eventDeleteId;
  cout << "Enter the Id of which you want to delete from database: ";
  cin >> eventDeleteId;
  for (int i = 0; i < eventList.size(); i++) {
    if (eventList[i]->eventId == eventDeleteId) {
      index = i;
    }
  }
  if (index == -1) {
    cout << "Event ID not found" << endl;
    return;
  }
  delete eventList[index]; // check what this does **************************
  eventList.erase(eventList.begin() + index);
  cout << "Cancelled Event deleted" << endl;
}

void ManagementSystem::showEventsInMonth(int checkMonth) {
  if (checkMonth < 1 || checkMonth > 12) {
    cout << "Invalid Month" << endl;
    return;
  }
  bool visitLoop = 0;
  for (int i = 0; i < eventList.size(); i++) {
    if (eventList[i]->eventDate.get_month() == checkMonth) {
      cout << "Event Id: " << eventList[i]->eventId << endl;
      cout << "Event Name: " << eventList[i]->nameOfEvent << endl;
      cout << "Event Date: " << eventList[i]->eventDate.day << "/"
           << eventList[i]->eventDate.month << "/"
           << eventList[i]->eventDate.year;

      visitLoop = 1;
    }
  }
  if (visitLoop == 0) {
    cout << "No events found in this month" << endl;
  }
}

void ManagementSystem::viewAllEvents(Event *event) {
  if (eventList.empty()) {
    cout << "No events to display." << endl;
    return;
  }
  for (int i = 0; i < eventList.size(); i++) {
    cout << "Event ID: " << eventList[i]->eventId << endl;
    cout << "Event Name: " << eventList[i]->nameOfEvent << endl;
    cout << "Event Date: " << eventList[i]->eventDate.get_day() << "/"
         << eventList[i]->eventDate.get_month() << "/"
         << eventList[i]->eventDate.get_year() << endl
         << endl;
  }
}

void ManagementSystem::cancelledCharges(int eventUpdateId) {
  bool loopVisit = 0;
  for (int i = 0; i < eventList.size(); i++) {
    if (eventList[i]->eventId == eventUpdateId) {

      if(eventList[i]->status!=0){
          if(eventList[i]->status==2){
              cout << "this is completed event" << endl;
          }
      }
        
      loopVisit = 1;
      eventList[i]->cancellationCharges(eventList[i]->status);
    }
  }
  if (loopVisit == 0) {
    cout << "Event ID not found" << endl;
  }
}

void ManagementSystem::generateInvitation(int ID) {
  for (int i = 0; i < eventList.size(); i++) {
    if (eventList[i]->eventId == ID) {
      eventList[i]->generate_invitation();
    }
  }
}

void ManagementSystem::addGuestForEvent(int Id1) {
  bool visitLoop = 0;
  for (int i = 0; i < eventList.size(); i++) {
    if (eventList[i]->eventId == Id1) {
      eventList[i]->add_guest();
      visitLoop = 1;
    }
  }
  if (visitLoop == 0) {
    cout << "Event ID not found" << endl;
  }
}

void ManagementSystem::menu() {
  Event *event = NULL;
  int choice;
  bool check = 1;
  do {
    cout
        << ".................................................................."
           "Menu..............................................................."
        << endl
        << endl;
    cout << "1. Add the new Event" << endl;
    cout << "2. Updating the existing bookings" << endl;
    cout << "3. Delete the cancelled bookings" << endl;
    cout << "4. Generate the invitation message for guests" << endl;
    cout << "5. Add Guests Information" << endl;
    cout << "6. Show all events" << endl;
    cout << "7. Monthly Data of Events" << endl;
    cout << "8. Complete pending payments" << endl;
    cout << "9. Complete Final Payments" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter the choice number : ";
    cin >> choice;
    cout << endl;
    switch (choice) {
    case 1: {
      int typeOfEvent;
      cout << ".........................................................."
              "Booking "
              "Event........................................................"
           << endl
           << endl;
      cout << "We offer the following types of events:" << endl;
      cout << "1. Short Event - Duration of 4 hours" << endl;
      cout << "2. Medium Event - Duration of 8 hours" << endl;
      cout << "3. Long Event - Duration of 12 hours" << endl;
      cout << "4. Extra Long Event - Duration of 24 hours" << endl << endl;
      cout << "Enter the choice for duration of the booking: ";
      cin >> typeOfEvent;
      switch (typeOfEvent) {
      case 1: {
        event = new shortEvent();
        storeEvent(event);
        break;
      }
      case 2: {
        event = new mediumEvent();
        storeEvent(event);
        break;
      }
      case 3: {
        event = new longEvent();
        storeEvent(event);
        break;
      }
      case 4: {
        event = new extraLongEvent();
        storeEvent(event);
        break;
      }
      default:
        cout << "Enter correct choice" << endl;
      }
      break;
    }
    case 2: {
      int eventUpdateId;
      cout << "Enter the event ID for which you want to update: ";
      cin >> eventUpdateId;

      cout << "What do you want to update: " << endl;
      cout << "1. Event Name" << endl;
      cout << "2. Event Date" << endl;
      cout << "3. Cancel the booking" << endl;
      int updateChoice;
      cout << "Enter the Choice Number: ";
      cin >> updateChoice;

      switch (updateChoice) {
      case 1: {
        storeUpdatedEvent(event, eventUpdateId, 1);
        break;
      }
      case 2: {
        storeUpdatedEvent(event, eventUpdateId, 2);
        break;
      }
      case 3: {
        cancelledCharges(eventUpdateId);
        cancelledId.push_back(eventUpdateId);
        break;
      }
      default:
        cout << "Enter correct choice" << endl;
      }

      break;
    }
    case 3: {
      deleteCancelledEvent();
      break;
    }
    case 4: {
      int evenId;
      cout << "Enter the EventId for which you want to generate invitation: "
           << endl;
      cin >> evenId;
      generateInvitation(evenId);
      break;
    }
    case 5: {
      int eventId1;
      cout << "Enter the EventId for which you want to add guests: " << endl;
      cin >> eventId1;
      addGuestForEvent(eventId1);
      break;
    }
    case 6: {
      viewAllEvents(event);
      break;
    }
    case 7: {
      int month;
      cout << "Enter the month for which you want to see events: ";
      cin >> month;
      showEventsInMonth(month);
      break;
    }
    case 8: {
        event->pending_payment();
      break;
    }
    case 9: {
        event->final_payment();
          break;
    }
    case 10:{
            return;
    }
    default:
      cout << "You have entered wrong choice number" << endl;
    }
  } while (check);
}

/*
cancel booking -> payment done or not check
update name not working
*/