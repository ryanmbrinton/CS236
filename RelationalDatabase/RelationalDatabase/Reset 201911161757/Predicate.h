#ifndef PREDICATE_H
#define PREDICATE_H

#include "TokenEnum.h"

class Predicate
{
private:
	Token tokenType;
	string predicateID;
	vector<string> listOfIDs;
public:
	Predicate(Token tokenIn, vector<string> stringsIn)
	{
		tokenType = tokenIn;
		listOfIDs = stringsIn;
		if (listOfIDs.size() > 0)
		{
			predicateID = listOfIDs.at(0);
			listOfIDs.erase(listOfIDs.begin(), listOfIDs.begin() + 1);
		}
	}
	string getID()
	{
		return predicateID;
	}
	vector<string> getListOfIDs()
	{
		return listOfIDs;
	}
	string toString()
	{
		ostringstream dataOSS;
		unsigned int i = 0;
		dataOSS << "  " << listOfIDs.at(i);
		if (tokenType != QUERIES)
		{
			dataOSS << "(";
		}
		for (i = 1; i < listOfIDs.size() - 1; ++i)
		{
			dataOSS << listOfIDs.at(i) << ",";
		}
		dataOSS << listOfIDs.at(i);
		if (tokenType != QUERIES)
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
};

#endif