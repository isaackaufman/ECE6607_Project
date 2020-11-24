#pragma once
#include <map>
#include <string>
#include <utility>

using namespace std;

struct ResourceID {
	uint8_t schoolID;
	uint8_t serviceID;
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

			// seed random
			srand(time(0));
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

		ResourceID intToResourceID(int resID)
		{
			ResourceID r = { (char)((resID & 0xFF000000) >> 24), (char)((resID & 0x00FF0000) >> 16), (uint16_t)(resID & 0x0000FFFF) };
			return r;
		}

		ResourceID generateResourceID(uint8_t schoolID, uint8_t serviceID)
		{
			// get a random student ID within the uint16_t range
			uint16_t studentID = rand() % 65536;

			ResourceID resID = { schoolID, serviceID, studentID };

			return resID;
		}

		string padToThreeDigits(string s)
		{
			while (s.length() < 3)
			{
				s = "0" + s;
			}

			return s;
		}

	private:
		map<int, string> schoolIDs;
		map<int, string> serviceIDs;
};