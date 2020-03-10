#ifndef RELATION_H
#define RELATION_H

#include "TokenEnum.h"
#include "Tuple.h"

class Relation
{
private:
	string relationName;
	vector<string> tupleNames;
	set<Tuple*> tupleList;
	void selectOperator(set<Tuple*> tuplesLeft, vector<string> toCheck)
	{
		bool resetIter = false;
		set<Tuple*>::iterator myIter = tuplesLeft.begin();
		while (myIter != tuplesLeft.end())
		{
			if (resetIter)
			{
				myIter = tuplesLeft.begin();
				resetIter = false;
			}
			
			if (!((*myIter)->potentialMatch(toCheck))) // set notation?
			{
				tuplesLeft.erase(myIter);
				resetIter = true;
				if (tuplesLeft.size() == 0)
				{
					return;
				}
				myIter--;
			}
			myIter++;
		}
	}
public:
	Relation(string relationNameIn, vector<string> relationSchemesIn)
	{
		relationName = relationNameIn;
		//relationSchemeList = relationSchemesIn;
		for (unsigned int i = 0; i < relationSchemesIn.size(); ++i)
		{
			tupleNames.push_back(relationSchemesIn.at(i));
		}
	}
	string getRelationName()
	{
		return relationName;
	}
	void populateTuples(vector<string> tuplesIn)
	{
		if (tuplesIn.size() != tupleNames.size())
		{
			return; // for testing: throw error, use break point here in IDE
		}
		tupleList.insert(new Tuple(tuplesIn)); // duplicate prevention?

	}
	void checkMatches(vector<string> toCheck)
	{
		vector<string> originalTupleNames = tupleNames;
		set<Tuple*> remainingTupleMatches = tupleList;
		cout << remainingTupleMatches.size() << endl;
		selectOperator(remainingTupleMatches, toCheck); // eliminate non-match rows
		cout << remainingTupleMatches.size() << endl;
		// if remainingTupleMatches.size() == 0, cout << "No" << endl;
		//use project to only show variables
		//use rename..?

		/*vector<bool> isConstant;
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			if (toCheck.at(i).at(0) == '\'')
			{
				isConstant.push_back(false);
			}
			else
			{
				isConstant.push_back(true);
			}
		}
		bool allConstant = true;
		bool allVariable = true;
		for (unsigned int i = 0; i < isConstant.size(); ++i)
		{
			if (isConstant.at(i))
			{
				allVariable = false;
			}
			else
			{
				allConstant = false;
			}
		}
		if (!allVariable)
		{
			for (unsigned int i = 0; i < isConstant.size(); ++i)
			{
				if (isConstant.at(i))
				{
					for (unsigned int j = 0; j < remainingTupleMatches.size(); ++j)
					{
						if (!remainingTupleMatches.at(j)->potentialMatch(toCheck))
						{
							// remove row, --j
						}
					}
				}
			}
		}
		else
		{
			//all variable, matching
		}*/
	}
};

#endif