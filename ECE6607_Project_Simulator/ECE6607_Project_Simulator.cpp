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

    int resourceID = 0;
    databaseInterface->get_appointments(resourceID);
    /* 
    * Create resource ID for student
    *   Prompt for school and service (show list of IDs)
    *   Generate random student ID and display final resource ID
    */


    // get list of open appointments and prompt to schedule one

    // return confirmation that appointment has been scheduled
    
}