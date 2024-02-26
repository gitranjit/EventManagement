#ifndef NOVELEVENT_H
#define NOVELEVENT_H

#include <string>
#include <vector>

using namespace std;

class Date {
protected:
  int day;
  int month;
  int year;

public:
  friend class ManagementSystem;
  Date();
  Date(int day, int month, int year);
  void set_date();
  void setNew_date();
  int get_day();
  int get_month();
  int get_year();
};

class Guests {
  string name;
  string mobile_number;

public:
  Guests();
  Guests(string name, string mobile_number);
  void setGuests();
  string getGuestsName();
  string getGuestsMob();
};

class Event {
private:
  static int eventCount;
  int breakfast_count = 0;
  int tea_count = 0;
  int meal_count = 0;
  int status = 0; // -1 for cancelled , 0 for pending , 1 for complete

  int hotelRooms = 0;

protected:
  int breakfastLim = 0;
  int mealLim = 0;
  int teaLim = 0;
  string nameOfEvent;
  float cost;
  float remained_cost = 0.0;
  int noOfGuests;
  float advance;
  float advanceCost;
  Date eventDate; // object of date class

public:
  Event();
  int eventId;

  friend class ManagementSystem;

  void setEventId();

  void setEventName();

  void setNewEventName();

  string getEventName();

  void setNoOfGuests();

  int getNoOfGuests();

  void add_guest();

  void setFood();

  void calculate_cost();

  void generate_invitation();

  void advance_payment();

  void cancellationCharges(int tempStatus);

  float getCost();

  void setEventDate();

  void setNewEventDate();

  void bookHotel();

  void pending_payment();

  void final_payment();
};

class ManagementSystem {
public:
  static vector<Event *> eventList;
  vector<int> cancelledId;
  void cancelledCharges(int Id2);
  void generateInvitation(int ID);
  void addGuestForEvent(int Id1);
  void storeEvent(Event *event);
  void storeUpdatedEvent(Event *event, int eventUpdateId, int flag);
  void deleteCancelledEvent();
  void showEventsInMonth(int month);
  void viewAllEvents(Event *event);
  void menu();
};

class shortEvent : public Event { // 4 hrs
public:
  shortEvent();
};

class mediumEvent : public Event { // 8 hrs
public:
  mediumEvent();
};

class longEvent : public Event { // 12 hrs
public:
  longEvent();
};

class extraLongEvent : public Event { // 24 hrs
public:
  extraLongEvent();
};

#endif // NOVELEVENT_H