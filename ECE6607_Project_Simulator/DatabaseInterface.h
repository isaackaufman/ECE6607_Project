#pragma once

#include <vector>
#include <list>
#include <ctime>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

struct Appointment
{
	int service;       // service ID for this appointment
	tm* time;          // appointment date and time
	bool studentsOnly; // appointment only for registered students of the school
	bool filled;       // appointment has been filled
	int studentID;     // ID of student who has filled this appointment
};

class DatabaseInterface
{
	public:
		DatabaseInterface(std::string databaseDirectory);

		list<Appointment> get_appointments(int resourceID);

		void confirm_appointment(Appointment appointment);

	private:
		string mDatabaseDirectory;

};