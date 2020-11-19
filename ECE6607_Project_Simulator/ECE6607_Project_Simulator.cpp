using namespace std;

#include <iostream>
#include <string>
#include "DatabaseInterface.h"
#include "ID.h"
#include "SchedulingInterface.h"

int main()
{

    ID* id = new ID();
    DatabaseInterface* databaseInterface = new DatabaseInterface("AppointmentDatabase");
    //SchedulingInterface* scheduler = new SchedulingInterface(*databaseInterface);

    map<int, string> schoolIDs = id->getSchoolIDs();
    map<int, string> serviceIDs = id->getServiceIDs();

    struct ResourceID rID = { 0, 0, 0 };
    /* 
    * Create resource ID for student
    *   Prompt for school and service (show list of IDs)
    *   Generate random student ID and display final resource ID
    */


    // get list of open appointments and prompt to schedule one
    databaseInterface->get_appointments(rID);

    // return confirmation that appointment has been scheduled

    struct tm timeInfo;
    timeInfo.tm_year = 120;
    timeInfo.tm_mon = 11;
    timeInfo.tm_mday = 12;
    timeInfo.tm_hour = 10;
    Appointment a = { "Georgia Institute of Technology", 0, &timeInfo, 1, 0 };
    databaseInterface->confirm_appointment(a);
    
}