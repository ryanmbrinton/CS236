#ifndef TUPLE_H
#define TUPLE_H

#include "TokenEnum.h"

class Tuple
{
private:
	vector<string> myTuples;
public:
	Tuple(vector<string> tuplesIn)
	{
		myTuples = tuplesIn;
	}
	bool potentialMatch(vector<string> toCheck)
	{
		// check constants
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			//cout << endl << endl << myTuples.at(i) << endl;
			//cout << toCheck.at(i) << endl << endl;
			if (toCheck.at(i).at(0) == '\'') // strings first, then variables
			{
				string tempConst = toCheck.at(i);
				//tempConst.pop_back();
				//tempConst.erase(0, 1);
				if (tempConst != myTuples.at(i))
				{
					//cout << myTuples.at(i) << endl;
					//cout << toCheck.at(i) << endl;
					
					cout << "returning false" << endl;
					return false;
				}
			}
		}
		// check variables
		return false; // temp, FIXME
	}
};

#endif