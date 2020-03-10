#ifndef DATABASE_H
#define DATABASE_H

#include "DatalogProgram.h"
#include "Relation.h"

class Database
{
private:
	vector<Predicate> mySchemes;
	vector<Predicate> myFacts;
	vector<Rule> myRules;
	vector<Predicate> myQueries;
	vector<Relation> myRelations;
public:
	Database(vector<Predicate> schemesIn, vector<Predicate> factsIn, vector<Rule> rulesIn,
		vector<Predicate> queriesIn)
	{
		mySchemes = schemesIn;
		myFacts = factsIn;
		myRules = rulesIn; // will handle in Project 4
		myQueries = queriesIn;
	}
	void populateRelations()
	{
		for (unsigned int i = 0; i < mySchemes.size(); ++i)
		{
			myRelations.push_back(Relation(mySchemes.at(i).getID(), mySchemes.at(i).getListOfStuff()));
		}
		for (unsigned int i = 0; i < myFacts.size(); ++i)
		{
			for (unsigned int j = 0; j < myRelations.size(); ++j)
			{
				if (myRelations.at(j).getRelationName() == myFacts.at(i).getID())
				{
					myRelations.at(j).populateTuples(myFacts.at(i).getListOfStuff());
					break;
				}
			}
		}
	}
	void answerQueries()
	{
		for (unsigned int i = 0; i < myQueries.size(); ++i)
		{
			vector<string> contentsList = myQueries.at(i).getListOfStuff();
			cout << myQueries.at(i).getID() << "(";
			for (unsigned int j = 0; j < contentsList.size(); ++j)
			{
				cout << contentsList.at(j);
				if (j + 1 < contentsList.size())
				{
					cout << ",";
				}
			}
			cout << ")? ";//getanswer, Yes(n) or No
			vector<string> myTupleNames;
			set<Tuple> myMatches;
			for (unsigned int j = 0; j < myRelations.size(); ++j)
			{
				if (myRelations.at(j).getRelationName() == myQueries.at(i).getID()) // break point
				{
					myRelations.at(j).checkMatches(contentsList, myTupleNames, myMatches);
					break;
				}
			}
			if (myMatches.size() == 0)
			{
				cout << "No" << endl;
			}
			else
			{
				cout << "Yes(" << myMatches.size() << ")" << endl;
				if (myMatches.size() == 1)
				{//skip print if allConst
					bool allConst = true;
					for (unsigned int j = 0; j < contentsList.size(); ++j)
					{
						if (contentsList.at(j).at(0) != '\'')
						{
							allConst = false;
							break;
						}
					}
					if (allConst)
					{
						continue;
					}
				}
				set<Tuple>::iterator myIter/* = tuplesLeft.begin()*/;
				for (myIter = myMatches.begin(); myIter != myMatches.end(); ++myIter)
				{
					Tuple tempTuple = (*myIter);
					tempTuple.printRemaining(myTupleNames);
				}
			}
		}
	}
};

#endif