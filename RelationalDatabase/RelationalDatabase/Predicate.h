#ifndef PREDICATE_H
#define PREDICATE_H

#include "TokenEnum.h"

class Predicate
{
private:
	Token tokenType;
	string leadID;
	vector<string> listOfStrings;
public:
	Predicate(Token tokenIn, string leadIDin, vector<string> stringsIn)
	{
		tokenType = tokenIn;
		leadID = leadIDin;
		listOfStrings = stringsIn;
	}
	string toString()
	{
		ostringstream dataOSS;
		unsigned int i = 0;
		dataOSS << "  " << listOfStrings.at(i);
		//if (tokenType != QUERIES)
		{
			dataOSS << "(";
		}
		for (i = 1; i < listOfStrings.size() - 1; ++i)
		{
			dataOSS << listOfStrings.at(i) << ",";
		}
		dataOSS << listOfStrings.at(i);
		//if (tokenType != QUERIES)
		{
			dataOSS << ")";
		}
		if (tokenType == FACTS)
		{
			dataOSS << ".";
		}
		if (tokenType == QUERIES)
		{
			dataOSS << "?";
		}
		return dataOSS.str();
	}

	string getID()
	{
		return leadID;
	}
	vector<string> getListOfStuff()
	{
		return listOfStrings;
	}
};

#endif