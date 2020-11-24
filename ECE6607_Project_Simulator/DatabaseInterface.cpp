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

Appointment DatabaseInterface::stoAppointment(string &line, string &path)
{
    stringstream ss(line);
    vector<string> strings;
    string s;
    while (getline(ss, s, ' ')) // parse an individual line by space delimiter
        strings.push_back(s);
    struct tm* timeInfo = new tm;
    timeInfo->tm_year = stoi(strings[1]); // set tm struct time values
    timeInfo->tm_mon = stoi(strings[2]);
    timeInfo->tm_mday = stoi(strings[3]);
    timeInfo->tm_hour = stoi(strings[4]);
    Appointment a = { path, stoi(strings[0]), timeInfo, stoi(strings[5]) != 0, stoi(strings[6]) != 0 }; // construct appointment
    return a;
}

list<Appointment> DatabaseInterface::getAppointments(struct ResourceID rID)
{
    fstream inFile;
    list<Appointment> temp = { };
    for (const auto& entry : fs::directory_iterator(mDatabaseDirectory))
    {
        string line;
        fs::path databases(entry.path());

        string path{ databases.filename().u8string() };

        inFile.open(databases, fstream::in); // open relevant school file
   
        while (getline(inFile, line)) // parse all lines of the database
        {
            Appointment a = stoAppointment(line, path);

            if (rID.serviceID == a.service && a.filled == 0) // check if service ID matches and appointment is not filled
            {
                char buffer[80];
                strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:00", a.time);
                string str(buffer);
                //cout << "University: " << a.schoolName << ", Resource ID: " << a.service << ", Date: " << str << ", Non-affiliated Students? " << std::boolalpha << a.studentsOnly << ", Filled? " << a.filled << endl;
                temp.push_back(a);
            }
        }
        inFile.close();
    }
    return temp;
}

void DatabaseInterface::confirmAppointment(Appointment &app)
{
    string input;
    ifstream inFile("AppointmentDatabase//" + app.schoolName);
    vector<string> lines;
    while (getline(inFile, input)) // copy all database lines to a vector (slow and not feasible for an actual database)
    {
        lines.push_back(input);
    }
    for (auto& line : lines) // check all appointments to see if it matches with the input appointment
    {
        Appointment a = stoAppointment(line, app.schoolName);

        char abuffer[80];
        char appbuffer[80];
        strftime(abuffer, sizeof(abuffer), "%d-%m-%Y %H:00", a.time);
        strftime(appbuffer, sizeof(appbuffer), "%d-%m-%Y %H:00", app.time);
        string astr(abuffer);
        string appstr(appbuffer);

        if (a.service == app.service && astr == appstr && a.studentsOnly == app.studentsOnly) // compare time strings
        {
            line.replace(line.size() - 1, 1, "1"); // replace the "filled" character
        }
    }
    
    inFile.close();
    ofstream outFile("AppointmentDatabase//" + app.schoolName); // overwrite the old database with the lines vector
    for (auto const& line : lines)
        outFile << line << '\n';
    outFile.close();
}