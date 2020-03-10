#ifndef PREDICATE_H
#define PREDICATE_H

#include "TokenEnum.h"

class Predicate
{
private:
	Token tokenType;
	vector<string> listOfStrings;
public:
	Predicate(Token tokenIn, vector<string> stringsIn)
	{
		tokenType = tokenIn;
		listOfStrings = stringsIn;
	}
	string toString()
	{
		ostringstream dataOSS;
		unsigned int i = 0;
		dataOSS << "  " << listOfStrings.at(i);
		if (tokenType != QUERIES)
		{
			dataOSS << "(";
		}
		for (i = 1; i < listOfStrings.size() - 1; ++i)
		{
			dataOSS << listOfStrings.at(i) << ",";
		}
		dataOSS << listOfStrings.at(i);
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