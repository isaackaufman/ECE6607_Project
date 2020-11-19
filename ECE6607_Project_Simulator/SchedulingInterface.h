#pragma once
#include "DatabaseInterface.h"

class SchedulingInterface
{
	public:
		SchedulingInterface(DatabaseInterface* databaseInterface);
	private:

		DatabaseInterface* mDatabaseInterface;
};

