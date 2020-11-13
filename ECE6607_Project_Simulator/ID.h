#pragma once
#include <map>
#include <string>
#include <utility>

using namespace std;

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

	private:
		map<int, string> schoolIDs;
		map<int, string> serviceIDs;
};