
#include <string>
#include <fstream>
#include <vector>
#include "DatabaseInterface.h"

using namespace std;


DatabaseInterface::DatabaseInterface(std::string databaseDirectory)
{
    mDatabaseDirectory = databaseDirectory;
}

list<Appointment> DatabaseInterface::get_appointments(int resourceID)
{
    for (const auto& entry : fs::directory_iterator(mDatabaseDirectory))
    {
        cout << entry.path() << endl;
    }

    // TODO determine structure of the files for each school
    // iterate through and pull a list of matching appointments (matching service, not filled, outside students allowed if applicable)
    Appointment a = Appointment();
    list<Appointment> temp = {a};

    return temp;
}

void DatabaseInterface::confirm_appointment(Appointment appointment)
{
    // open corresponding school file and set the filled bool and the student ID
}