#ifndef RULE_H
#define RULE_H

#include "TokenEnum.h"

class Rule
{
private:
	vector<string> listOfIDsBefore;
	vector<string> listOfPredicatesAfter;
public:
	Rule(vector<string> IDsIn, vector<string> predicatesIn)
	{
		listOfIDsBefore = IDsIn;
		listOfPredicatesAfter = predicatesIn;
	}
	string toString()
	{
		ostringstream dataOSS;
		unsigned int i = 0;
		dataOSS << "  " << listOfIDsBefore.at(i) << "(";
		for (i = 1; i < listOfIDsBefore.size() - 1; ++i)
		{
			dataOSS << listOfIDsBefore.at(i) << ",";
		}
		dataOSS << listOfIDsBefore.at(i) << ") :- ";
		for (i = 0; i < listOfPredicatesAfter.size() - 2; ++i)
		{
			dataOSS << listOfPredicatesAfter.at(i);
			++i;
			dataOSS << listOfPredicatesAfter.at(i) << ",";
		}
		dataOSS << listOfPredicatesAfter.at(i);
		++i;
		dataOSS << listOfPredicatesAfter.at(i) << ".";
		return dataOSS.str();
	}
};

#endif