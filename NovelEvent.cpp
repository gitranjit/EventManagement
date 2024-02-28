#include "NovelEvent.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

float Fmax(float a, float b) {
    if (a > b)
        return a;
    return b;
}

vector<Event*> ManagementSystem::eventList;

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
    }
    else {
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
int Event::get_breakfastLim() { return breakfastLim; }
int Event::get_mealLim() { return mealLim; }
int Event::get_teaLim() { return teaLim; }
int Event::get_breakfast_count() { return breakfast_count; }
int Event::get_tea_count() { return tea_count; }
int Event::get_meal_count() { return meal_count; }
void Event::set_remained_cost(int cost) { remained_cost = cost; }

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

void ManagementSystem::calculate_cost(int id) {
    for (int i = 0; i < eventList.size(); i++) {
        if (eventList[i]->getEventId() == id) {
            eventList[i]->setFood();
            if (eventList[i]->get_breakfast_count() >=
                eventList[i]->get_breakfastLim()) {
                eventList[i]->set_remained_cost(eventList[i]->get_remained_cost() +
                    (eventList[i]->get_breakfast_count() -
                        eventList[i]->get_breakfastLim()) *
                    50);
            }

            if (eventList[i]->get_tea_count() >= eventList[i]->get_teaLim()) {
                eventList[i]->set_remained_cost(
                    eventList[i]->get_remained_cost() +
                    (eventList[i]->get_tea_count() - eventList[i]->get_teaLim()) * 10);
            }

            if (eventList[i]->get_meal_count() >= eventList[i]->get_mealLim()) {
                eventList[i]->set_remained_cost(
                    eventList[i]->get_remained_cost() +
                    (eventList[i]->get_meal_count() - eventList[i]->get_mealLim()) *
                    100);
            }
        }
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

void Event::pending_payment() {
    bool visitLoop = 0;
    int eventPendingId;
    cout << "Enter Id of event to complete pending payment: ";
    cin >> eventPendingId;

    for (int i = 0; i < ManagementSystem::eventList.size(); i++) {
        if (eventPendingId == ManagementSystem::eventList[i]->eventId) {

            ManagementSystem::eventList[i]->advance_payment();

            visitLoop = 1;
        }
    }

    if (visitLoop == 0) {
        cout << "No event found with this id" << endl;
    }
}

void Event::advance_payment() {
    if (status >= 1) {
        cout << "Event is already paid" << endl;
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
    }
    else {
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

    if (tempStatus == 1) {
        if (cost * 0.3 < 15000) {
            cout << "You have to pay " << Fmax(float(0), (cost * 0.3) - advance)
                << " now as cancellation charges" << endl;
        }
        else {
            cout << "You have to pay " << Fmax(15000 - advance, float(0))
                << " now as cancellation charges" << endl;
        }
    }

    if (cost * 0.3 < 15000) {
        cout << "You have to pay " << cost * 0.3 << " now as cancellation charges"
            << endl;
    }
    else {
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
void Event::setStatus(int inputStatus) { status = inputStatus; }
void Event::setNewEventDate() { eventDate.setNew_date(); }
int Event::getEventId() { return eventId; }
int Event::getStatus() { return status; }
int Event::get_remained_cost() { return remained_cost; }
void ManagementSystem::eventStatusMonth() {
    int inputMonth, inputStatus;
    cout << "Enter Month: ";
    cin >> inputMonth;

    cout << "Enter Status (-1 for cancelled ,1 for pending    2 for completed) "
        "events: ";
    cin >> inputStatus;

    for (int i = 0; i < ManagementSystem::eventList.size(); i++) {
        if (ManagementSystem::eventList[i]->eventDate.get_month() == inputMonth &&
            ManagementSystem::eventList[i]->getStatus() == inputStatus) {
            cout << "Event Id: " << ManagementSystem::eventList[i]->getEventId()
                << "    "
                << "Event Name: " << ManagementSystem::eventList[i]->getEventName()
                << endl;
        }
    }
}

void Event::bookHotel() {
    cout << "Enter the number of hotel rooms required: ";
    cin >> hotelRooms;
    cost += 500 * hotelRooms;
    remained_cost = cost;
}

void ManagementSystem::final_payment() {

    int eventPayId = 0;
    cout << "Enter Id of event to complete the payment process: ";
    cin >> eventPayId;

    bool visitLoop = 0;

    for (int i = 0; i < ManagementSystem::eventList.size(); i++) {
        if (ManagementSystem::eventList[i]->eventId == eventPayId) {
            int currStatus = ManagementSystem::eventList[i]->status;
            if (currStatus != 1) {
                if (currStatus == 0)
                    cout << "Your payment is pending" << endl;
                else if (currStatus == 2)
                    cout << "Your payment is already done" << endl;

                return;
            }
            calculate_cost(eventPayId);
            cout << "You have to pay "
                << ManagementSystem::eventList[i]->get_remained_cost() << " now"
                << endl;

            cout << "payment done";

            ManagementSystem::eventList[i]->setStatus(2);

            ManagementSystem::eventList[i]->set_remained_cost(0);
            visitLoop = 1;
        }
    }

    if (visitLoop == 0) {
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

void ManagementSystem::storeEvent(Event* event) {
    event->setEventName();
    event->setEventDate();
    event->setNoOfGuests();
    // event->setFood();
    // event->calculate_cost();
    event->bookHotel();
    event->advance_payment();
    eventList.push_back(event);
}

void ManagementSystem::storeUpdatedEvent(Event* event, int eventUpdateId,
    int flag) {

    bool loopFlag = 0;

    for (int i = 0; i < eventList.size(); i++) {
        if (eventList[i]->eventId == eventUpdateId) {
            loopFlag = 1;
            if (flag == 1) {
                eventList[i]->setNewEventName();
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

void ManagementSystem::viewAllEvents() {
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

            if (eventList[i]->status != 0) {
                if (eventList[i]->status == 2) {
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

void ManagementSystem::adminMenu() {
    // Admin functionalities

    int choice;
    bool check = true;
    do {
        cout << "Admin Menu:" << endl;

        cout << "1. Delete Cancelled Bookings" << endl;
        cout << "2. Show All Events" << endl;
        cout << "3. Monthly Data of Events" << endl;
        cout << "4. Show All Events for perticular status in a Month" << endl;
        cout << "5. complete final payment" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            deleteCancelledEvent();
            break;
        case 2:
            viewAllEvents();
            break;
        case 3:
            int inputMonth;
            cout << "Enter Month number : ";
            cin >> inputMonth;
            showEventsInMonth(inputMonth);
            break;
        case 4:
            eventStatusMonth();
            break;
        case 5:
            final_payment();
            break;
        case 6:
            return;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (check);
}

void ManagementSystem::userMenu() {

    Event* event = NULL;

    // User functionalities
    int choice;
    bool check = true;
    do {
        cout << "User Menu:" << endl;
        cout << "1. Book Event" << endl;
        cout << "2. Update Booking" << endl;
        cout << "3. Generate Invitation for Event" << endl;
        cout << "4. Add Guests Information" << endl;
        cout << "5. Complete Pending Payments" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
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
        case 2:
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
        case 3:
            int evenId;
            cout << "Enter the EventId for which you want to generate invitation: "
                << endl;
            cin >> evenId;
            generateInvitation(evenId);
            break;
        case 4:
            int eventId1;
            cout << "Enter the EventId for which you want to add guests: " << endl;
            cin >> eventId1;
            addGuestForEvent(eventId1);
            break;
        case 5:
            event->pending_payment();
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (check);
}

void ManagementSystem::menu() {
    int userType;
    while (true) {
        cout << "Select User Type:" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
        case 1: { // Admin
            string password;
            cout << "Enter the password for the admin: ";
            cin >> password;
            if (password == "admin") {
                adminMenu();
            }
            break;
        }
        case 2: // User
            userMenu();
            break;
        case 3:
            cout << "Exiting the program." << endl;
            return;
        default:
            cout << "Invalid choice. Exiting." << endl;
        }
    }
}
