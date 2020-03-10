#ifndef RELATION_H
#define RELATION_H

#include "TokenEnum.h"
#include "Tuple.h"

class Relation
{
private:
	string relationName;
	vector<string> tupleNames;
	vector<Tuple*> tupleList;
	vector<Tuple*> selectOperator(vector<Tuple*> tuplesIn, vector<string> toCheck)
	{
		for (unsigned int i = 0; i < tuplesIn.size(); ++i)
		{
			if (!tuplesIn.at(i)->potentialMatch(toCheck))
			{
				// remove row, --i
			}
		}
		return tuplesIn;
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
		tupleList.push_back(new Tuple(tuplesIn)); // duplicate prevention?

	}
	void checkMatches(vector<string> toCheck)
	{
		vector<string> originalTupleNames = tupleNames;
		vector<Tuple*> remainingTupleMatches = tupleList;

		remainingTupleMatches = selectOperator(remainingTupleMatches, toCheck); // eliminate non-matches


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