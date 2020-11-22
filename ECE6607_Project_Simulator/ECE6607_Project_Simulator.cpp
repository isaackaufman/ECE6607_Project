using namespace std;

#include <iostream>
#include <string>
#include "DatabaseInterface.h"
#include "ID.h"

int main()
{

    ID* id = new ID();
    DatabaseInterface* databaseInterface = new DatabaseInterface("AppointmentDatabase");

    map<int, string> schoolIDs = id->getSchoolIDs();
    map<int, string> serviceIDs = id->getServiceIDs();

    /* 
    * Create resource ID for student
    *   Prompt for school and service (show list of IDs)
    *   Generate random student ID and display final resource ID
    */
    int schoolID;
    int serviceID;

    map<int, string>::iterator it;
    for (it = schoolIDs.begin(); it != schoolIDs.end(); it++)
    {
        cout << to_string(it->first) << " : " << it->second << endl;
    }
    cout << "Select your school: ";
    cin >> schoolID;

    for (it = serviceIDs.begin(); it != serviceIDs.end(); it++)
    {
        cout << to_string(it->first) << " : " << it->second << endl;
    }
    cout << "Select your service: ";
    cin >> serviceID;

    struct ResourceID* rID = id->generateResourceID(schoolID, serviceID);

    // get list of open appointments and prompt to schedule one
    list<Appointment> appointments = databaseInterface->getAppointments(*rID);
    
    if (appointments.size() == 0)
    {
        cout << "Sorry, there are no open appointments." << endl;
        return 1;
    }

    int i = 1;
    int selectedAppt;
    for (const Appointment appt : appointments)
    {
        cout << i << " : " << appt.schoolName << " - "
            << appt.time->tm_mon << "/" << appt.time->tm_mday
            << " " << appt.time->tm_hour << ":00" << endl;
        i++;
    }
    cout << "Select an appointment to schedule: ";
    cin >> selectedAppt;

    list<Appointment>::iterator apptIt = appointments.begin();
    advance(apptIt, (selectedAppt - 1));
    
    Appointment a = { apptIt->schoolName, apptIt->service, apptIt->time, apptIt->studentsOnly, apptIt->filled };
    databaseInterface->confirmAppointment(a);

    // return confirmation that appointment has been scheduled
    cout << "Appointment successfully scheduled!";
    
    return 0;
}