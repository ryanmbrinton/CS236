#ifndef RELATION_H
#define RELATION_H

#include "TokenEnum.h"
#include "Tuple.h"

class Relation
{
private:
	string relationName;
	vector<string> tupleNames;
	set<Tuple> tupleList;
	void selectOperator(set<Tuple> &tuplesLeft, vector<string> toCheck)
	{
		bool checkID = false;
		bool fullBreak = false;
		vector<string> myIDs;
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			if (toCheck.at(i).at(0) != '\'')
			{
				if (myIDs.size())
				{
					for (unsigned int j = 0; j < myIDs.size(); ++j)
					{
						if (toCheck.at(i) == myIDs.at(j))
						{
							checkID = true;
							fullBreak = true;
							break;
						}
					}
					if (fullBreak)
					{
						break;
					}
				}
				myIDs.push_back(toCheck.at(i));
			}
		}
		set<Tuple>::iterator myIter;
		for (myIter = tupleList.begin(); myIter != tupleList.end(); ++myIter)
		{
			Tuple testTuple = (*myIter);
			if (testTuple.isMatch(toCheck, checkID))
			{
				tuplesLeft.insert(testTuple);
			}
		}
	}
	void projectOperator(vector<string> &tupleNamesIn, set<Tuple>& tupleMatches, vector<string> &toCheck)
	{
		if (tupleNames.size() != toCheck.size())
		{
			//IDE break point, error
		}
		if (tupleNames.size() != tupleMatches.size())
		{
			//IDE break point, error
		}
		set<Tuple>::iterator iter;
		set<Tuple> newTuples;
		vector<bool> toChange;
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			toChange.push_back(false);
		}
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			if (!toChange.at(i))
			{
				if (toCheck.at(i).at(0) == '\'')
				{
					toChange.at(i) = true;
				}
				else
				{
					for (unsigned int j = i + 1; j < toCheck.size(); ++j)
					{
						if (toCheck.at(i) == toCheck.at(j))
						{
							toChange.at(j) = true;
						}
					}
				}
			}
		}
		for (iter = tupleMatches.begin(); iter != tupleMatches.end(); ++iter)
		{
			Tuple myTuple = *iter;
			for (int i = toChange.size() - 1; i >= 0; --i)
			{
				if (toChange.at(i))
				{
					myTuple.erase(myTuple.begin() + i);
				}
			}
			newTuples.insert(myTuple);
		}
		tupleMatches = newTuples;
		for (int i = toChange.size() - 1; i >= 0; --i)
		{
			if (toChange.at(i))
			{
				toCheck.erase(toCheck.begin() + i);
				tupleNamesIn.erase(tupleNamesIn.begin() + i);
			}
		}
	}
	void renameOperator(vector<string>& tupleNamesIn, vector<string>& toCheck)
	{
		if (tupleNamesIn.size() != toCheck.size())
		{
			//error, IDE breakpoint
		}
		for (unsigned int i = 0; i < tupleNamesIn.size(); ++i)
		{
			tupleNamesIn.at(i) = toCheck.at(i);
		}
	}
	void projectAssist(vector<string>& tupleNamesIn, set<Tuple>& tupleMatches, vector<string>& toCheck,
		unsigned int& i, set<Tuple>::iterator& iter, set<Tuple>& newTuples)
	{
		for (unsigned int j = i + 1; j < toCheck.size(); ++j)
		{
			if (toCheck.at(i) == toCheck.at(j))
			{
				for (iter = tupleMatches.begin(); iter != tupleMatches.end(); ++iter)
				{
					Tuple myTuple = *iter;
					myTuple.erase(myTuple.begin() + j);
					newTuples.insert(myTuple);
				}
				toCheck.erase(toCheck.begin() + j);
				tupleNamesIn.erase(tupleNamesIn.begin() + j);
				--j;
				projectAssist(tupleNamesIn, tupleMatches, toCheck, j, iter, newTuples);
				tupleMatches = newTuples;
			}
		}
	}
public:
	Relation(string relationNameIn, vector<string> relationSchemesIn)
	{
		relationName = relationNameIn;
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
		Tuple myTupleToAdd(tuplesIn);
		tupleList.insert(myTupleToAdd);
	}
	void checkMatches(vector<string> &toCheck, vector<string>& tupleNamesIn, set<Tuple> &tupleMatches)
	{
		selectOperator(tupleMatches, toCheck); // add matching rows
		tupleNamesIn = tupleNames;
		if (tupleMatches.size() == 0)
		{
			return;
		}
		bool allConst = true;
		for (unsigned int i = 0; i < toCheck.size(); ++i)
		{
			if (toCheck.at(i).at(0) != '\'')
			{
				allConst = false;
				break;
			}
		}
		if (allConst)
		{
			if (tupleMatches.size() <= 1)
			{
				return;
			}
			else
			{
				//error, set IDE breakpoint
			}
		}
		projectOperator(tupleNamesIn, tupleMatches, toCheck);
		renameOperator(tupleNamesIn, toCheck);
		return;
	}
};

#endif