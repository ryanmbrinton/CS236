#ifndef TUPLE_H
#define TUPLE_H

#include "TokenEnum.h"

class Tuple : public vector<string>
{
private:
	//vector<string> myTuples;
public:
	Tuple(vector<string> tuplesIn) : vector<string>(tuplesIn)
	{
		//myTuples = tuplesIn;
	}
	bool isMatch(vector<string> toCheck, bool checkID)
	{
		vector<bool> alreadyCheckedVars;
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			alreadyCheckedVars.push_back(false);
		}
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			string tempConst = toCheck.at(i);
			if (tempConst.at(0) == '\'') // strings first, then variables
			{
				alreadyCheckedVars.at(i) = true;
				if (tempConst != at(i))
				{
					return false;
				} // else, the constant matches
			}
		}
		if (checkID)
		{
			for (unsigned int i = 0; i < toCheck.size(); ++i)
			{
				string tempConst = toCheck.at(i);
				if (!alreadyCheckedVars.at(i))
				{
					if (tempConst.at(0) != '\'')
					{
						alreadyCheckedVars.at(i) = true;
						for (unsigned int j = 0; j < toCheck.size(); ++j)
						{
							if (!alreadyCheckedVars.at(j))
							{
								if (tempConst == toCheck.at(j))
								{
									alreadyCheckedVars.at(j) = true;
									if (at(i) != at(j))
									{
										return false;
									}
								}
							}
						}
					}
					else
					{
						//error, set break point in IDE
					}
				}



				if (tempConst.at(0) != '\'') // check variables
				{
					if (checkID) // if checkID is false, there are no variables
					{
						for (unsigned int j = 0; j < toCheck.size(); ++j)
						{
							if (!alreadyCheckedVars.at(j))
							{

							}

						}
					}
				}
			}
		}
		return true;
	}
	void printRemaining(vector<string> &tupleNames)
	{
		if (tupleNames.size() != size())
		{
			//error, IDE breakpoint
		}
		cout << "  ";
		for (unsigned int i = 0; i < size(); ++i)
		{
			cout << tupleNames.at(i);
			cout << "=";
			cout << at(i);
			if (i < size() - 1)
			{
				cout << ", ";
			}
		}
		cout << endl;
		return;
	}
};

#endif