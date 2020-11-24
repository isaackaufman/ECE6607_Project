#pragma once

#include <vector>
#include <list>
#include <ctime>
#include <iostream>
#include <filesystem>
#include "ID.h"

using namespace std;
namespace fs = filesystem;

struct Appointment
{
	string schoolName; // school this appointment this belong to
	int service;       // service ID for this appointment
	tm* time;          // appointment date and time
	bool studentsOnly; // appointment only for registered students of the school
	bool filled;       // appointment has been filled
};

class DatabaseInterface
{
	public:
		DatabaseInterface(std::string databaseDirectory);

		list<Appointment> getAppointments(struct ResourceID rID);

		void confirmAppointment(Appointment &app);

	private:
		Appointment stoAppointment(string &line, string &path);

		string mDatabaseDirectory;

};