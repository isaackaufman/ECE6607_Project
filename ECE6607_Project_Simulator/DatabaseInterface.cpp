#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "DatabaseInterface.h"

using namespace std;

#define N 8


DatabaseInterface::DatabaseInterface(std::string databaseDirectory)
{
    mDatabaseDirectory = databaseDirectory;
}

list<Appointment> DatabaseInterface::get_appointments(struct ResourceID rID)
{
    fstream inFile;
    list<Appointment> temp = { };
    for (const auto& entry : fs::directory_iterator(mDatabaseDirectory))
    {
        string line;
        fs::path databases(entry.path());

        cout << databases.filename() << endl;

        string path_string{ databases.filename().u8string() };

        inFile.open(databases, fstream::in); // open relevant school file
   
        getline(inFile, line); // discard first formatting line
        while (getline(inFile, line))
        {
            stringstream ss (line);
            vector<string> strings;
            string s;
            while (getline(ss, s, ' ')) 
                strings.push_back(s);
            struct tm timeInfo;
            char buffer[80];
            timeInfo.tm_year = stoi(strings[1]);
            timeInfo.tm_mon = stoi(strings[2]);
            timeInfo.tm_mday = stoi(strings[3]);
            timeInfo.tm_hour = stoi(strings[4]);
            Appointment a = { path_string, stoi(strings[0]), &timeInfo, stoi(strings[5]) != 0, stoi(strings[6]) != 0 };

            if (rID.serviceID == a.service && a.filled == 0)
            {
                strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:00", a.time);
                string str(buffer);
                cout << "University: " << a.schoolName << ", Resource ID: " << a.service << ", Date: " << str << ", Non-affiliated Students? " << std::boolalpha << a.studentsOnly << ", Filled? " << a.filled << endl;
                temp.push_back(a);
            }
        }
        inFile.close();
    }

    // TODO determine structure of the files for each school
    // iterate through and pull a list of matching appointments (matching service, not filled, outside students allowed if applicable)
    
    
    return temp;
}

void DatabaseInterface::confirm_appointment(Appointment appointment)
{
    string line;
    fstream inFile;
    inFile.open("AppointmentDatabase//" + appointment.schoolName, fstream::in); // open relevant school file
    getline(inFile, line);
    cout << line;
}