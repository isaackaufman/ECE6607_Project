#pragma once
#include <map>
#include <string>
#include <utility>

using namespace std;

struct ResourceID {
	char schoolID;
	char serviceID;
	uint16_t studentID;
};

class ID
{
	public:
		ID()
		{
			// populate school IDs
			schoolIDs[2] = "Georgia Institute of Technology";
			schoolIDs[102] = "Emory University";
			schoolIDs[104] = "Georgia State University";
			schoolIDs[103] = "Kennesaw State University";

			// populate service IDs
			serviceIDs[0] = "counseling";
			serviceIDs[1] = "gym";
			serviceIDs[2] = "swimming pool";
		}

		map<int, string> getSchoolIDs()
		{
			return schoolIDs;
		}

		map<int, string> getServiceIDs()
		{
			return serviceIDs;
		}

		int resourceIDtoInt(ResourceID* resID)
		{
			return ((resID->schoolID << 24) + (resID->serviceID << 16) + resID->studentID);
		}

		ResourceID* intToResourceID(int resID)
		{
			ResourceID r = { (char)(resID & 0xFF000000), (char)(resID & 0x00FF0000), (uint16_t)(resID & 0x0000FFFF) };
			return &r;
		}

	private:
		map<int, string> schoolIDs;
		map<int, string> serviceIDs;
};