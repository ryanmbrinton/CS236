#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include "TokenData.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram
{
private:
	vector<TokenData*> myTokens;
	vector<Predicate*> mySchemes;
	vector<Predicate*> myFacts;
	vector<Rule*> myRules;
	vector<Predicate*> myQueries;
	vector<string> myDomain;
	bool isValid;
	unsigned int i;
	unsigned int j;
	void scheme(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}
		
		if (myTokens.at(i)->getTokenType() == ID)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == LEFT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		idList(myTokens);
		
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}
	void idList(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == COMMA)
		{
			++i;
			if (myTokens.at(i)->getTokenType() == ID)
			{
				++i;
				idList(myTokens);
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
		else // might be lambda - if so, only followed by RIGHT_PAREN
		{
			if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
			{
				return;
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}
	void schemeList(vector<TokenData*> myTokens) // only followed by FACTS
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID) // scheme - first ID
		{
			scheme(myTokens);
			schemeList(myTokens);
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == FACTS) // follow set for lambda
			{
				return;
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}

	void factList(vector<TokenData*> tokensIn) // only followed by RULES
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID)
		{
			fact(myTokens);
			factList(myTokens);
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == RULES)
			{
				return;
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}

	void fact(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == LEFT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == STRING)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		stringList(myTokens);

		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == PERIOD)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}

	void stringList(vector<TokenData*> tokensIn) // only followed by RIGHT_PAREN
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN) // lambda
		{
			return;
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == COMMA)
			{
				++i;
				if (myTokens.at(i)->getTokenType() == STRING)
				{
					++i;
					stringList(myTokens);
				}
				else
				{
					isValid = false;
					cout << "Failure!" << endl;
					cout << "  " << myTokens.at(i)->toString() << endl;
					return;
				}
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}

	void ruleList(vector<TokenData*> tokensIn) // only followed by QUERIES
	{
		if (!isValid)
		{
			return;
		}
		
		if (myTokens.at(i)->getTokenType() == QUERIES) // lambda
		{
			return;
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == ID) // first of headPredicate
			{
				rule(myTokens);
				ruleList(myTokens);
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}

	void rule(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID)
		{
			headPredicate(myTokens);
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == COLON_DASH)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		predicate(myTokens);

		predicateList(myTokens);

		if (!isValid)
		{
			return;
		}

		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == PERIOD)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}

	void headPredicate(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == LEFT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == ID)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		idList(myTokens);

		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}

	void predicate(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}
		
		if (myTokens.at(i)->getTokenType() == ID)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		if (myTokens.at(i)->getTokenType() == LEFT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		parameter(myTokens);

		parameterList(myTokens);

		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}

	void predicateList(vector<TokenData*> tokensIn) // only followed by PERIOD
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == PERIOD)
		{
			return;
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == COMMA)
			{
				++i;
				predicate(myTokens);
				predicateList(myTokens);
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}

	void parameter(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == STRING)
		{
			++i;
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == ID)
			{
				++i;
			}
			else
			{
				if (myTokens.at(i)->getTokenType() == LEFT_PAREN)
				{
					expression(myTokens);
				}
				else
				{
					isValid = false;
					cout << "Failure!" << endl;
					cout << "  " << myTokens.at(i)->toString() << endl;
					return;
				}
			}
		}

		
	}
	
	void parameterList(vector<TokenData*> tokensIn) // only followed by RIGHT_PAREN
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
		{
			return;
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == COMMA)
			{
				++i;
				parameter(myTokens);
				parameterList(myTokens);
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}
	
	void expression(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == LEFT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}

		parameter(myTokens);

		myOperator(myTokens);

		parameter(myTokens);

		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == RIGHT_PAREN)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}
	
	void myOperator(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == ADD)
		{
			++i;
		}
		else
		{
			if (myTokens.at(i)->getTokenType() == MULTIPLY)
			{
				++i;
			}
			else
			{
				isValid = false;
				cout << "Failure!" << endl;
				cout << "  " << myTokens.at(i)->toString() << endl;
				return;
			}
		}
	}
	
	void query(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		predicate(myTokens);

		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == Q_MARK)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return;
		}
	}
	
	void queryList(vector<TokenData*> tokensIn)
	{
		if (!isValid)
		{
			return;
		}

		if (myTokens.at(i)->getTokenType() == MEOF)
		{
			return;
		}
		else
		{
			query(myTokens);
			queryList(myTokens);
		}
	}
public:
	DatalogProgram(vector<TokenData*> tokensIn)
	{
		myTokens = tokensIn;
		isValid = true; // true until proven false
		i = 0;
		j = 2; // 0 is SCHEMES, 1 is COLON
	}

	bool isSyntaxValid()
	{
		if (myTokens.at(i)->getTokenType() == SCHEMES)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == COLON)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		scheme(myTokens);

		schemeList(myTokens);

		if (!isValid)
		{
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == FACTS)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == COLON)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		factList(myTokens);

		if (!isValid)
		{
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == RULES)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == COLON)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		ruleList(myTokens);

		if (!isValid)
		{
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == QUERIES)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		if (myTokens.at(i)->getTokenType() == COLON)
		{
			++i;
		}
		else
		{
			isValid = false;
			cout << "Failure!" << endl;
			cout << "  " << myTokens.at(i)->toString() << endl;
			return isValid;
		}

		query(myTokens);

		queryList(myTokens);

		return isValid;
	}

	void generateLists()
	{
		vector<string> schemeStrings;
		while (j < myTokens.size()) // populate schemes
		{
			if (myTokens.at(j)->getTokenType() == ID)
			{
				schemeStrings.push_back(myTokens.at(j)->getString());

			}
			if (myTokens.at(j)->getTokenType() == RIGHT_PAREN)
			{
				mySchemes.push_back(new Predicate(SCHEMES, schemeStrings));
				schemeStrings.clear();
			}
			++j;
			if (myTokens.at(j)->getTokenType() == FACTS)
			{
				break;
			}
		}
		vector<string> factStrings;
		while (j < myTokens.size()) // populate facts
		{
			if (myTokens.at(j)->getTokenType() == ID)
			{
				factStrings.push_back(myTokens.at(j)->getString());

			}
			if (myTokens.at(j)->getTokenType() == STRING)
			{
				factStrings.push_back(myTokens.at(j)->getString());
				bool notDuplicate = true;
				string stringToFind = myTokens.at(j)->getString();
				for (unsigned int k = 0; k < myDomain.size(); ++k)
				{
					if (stringToFind == myDomain.at(k))
					{
						notDuplicate = false;
						k = myDomain.size();
					}
				}
				if (notDuplicate)
				{
					myDomain.push_back(myTokens.at(j)->getString());
				}
			}
			if (myTokens.at(j)->getTokenType() == PERIOD)
			{
				myFacts.push_back(new Predicate(FACTS, factStrings));
				factStrings.clear();
			}
			++j;
			if (myTokens.at(j)->getTokenType() == RULES)
			{
				break;
			}
		}
		vector<string> ruleStringsBefore;
		vector<string> ruleStringsAfter;
		bool before = true;
		bool leadID = true;
		unsigned int parCounter = 0;
		ostringstream dataOSS;
		while (j < myTokens.size()) // populate rules
		{
			if (before)
			{
				if (myTokens.at(j)->getTokenType() == ID)
				{
					ruleStringsBefore.push_back(myTokens.at(j)->getString());
				}
				if (myTokens.at(j)->getTokenType() == COLON_DASH)
				{
					before = false;
				}
			}
			else
			{
				if (myTokens.at(j)->getTokenType() == ID)
				{
					if (leadID)
					{
						ruleStringsAfter.push_back(myTokens.at(j)->getString());
						leadID = false;
					}
					else
					{
						dataOSS << myTokens.at(j)->getString();
					}
				}
				else if (myTokens.at(j)->getTokenType() == LEFT_PAREN)
				{
					++parCounter;
					dataOSS << myTokens.at(j)->getString();
				}
				else if (myTokens.at(j)->getTokenType() == RIGHT_PAREN)
				{
					--parCounter;
					dataOSS << myTokens.at(j)->getString();
					if (parCounter == 0)
					{
						ruleStringsAfter.push_back(dataOSS.str());
						dataOSS.str("");
						dataOSS.clear();
						leadID = true;
					}
				}
				else if (myTokens.at(j)->getTokenType() == COMMA)
				{
					if (parCounter)
					{
						dataOSS << myTokens.at(j)->getString();
					}
				}
				else if (myTokens.at(j)->getTokenType() == PERIOD)
				{
					myRules.push_back(new Rule(ruleStringsBefore, ruleStringsAfter));
					ruleStringsBefore.clear();
					ruleStringsAfter.clear();
					before = true;
				}
				else
				{
					dataOSS << myTokens.at(j)->getString();
				}
			}
			++j;
			if (myTokens.at(j)->getTokenType() == QUERIES)
			{
				break;
			}
		}
		vector<string> queryStrings;
		while (j < myTokens.size()) // populate queries
		{
			if (leadID)
			{
				if (myTokens.at(j)->getTokenType() == ID)
				{
					queryStrings.push_back(myTokens.at(j)->getString());
					leadID = false;
				}
			}
			else
			{
				if (myTokens.at(j)->getTokenType() == ID)
				{
					dataOSS << myTokens.at(j)->getString();
				}
				else if (myTokens.at(j)->getTokenType() == LEFT_PAREN)
				{
					++parCounter;
					dataOSS << myTokens.at(j)->getString();
				}
				else if (myTokens.at(j)->getTokenType() == RIGHT_PAREN)
				{
					--parCounter;
					dataOSS << myTokens.at(j)->getString();
					if (parCounter == 0)
					{
						queryStrings.push_back(dataOSS.str());
						dataOSS.str("");
						dataOSS.clear();
						if (myTokens.at(j + 1)->getTokenType() == Q_MARK)
						{
							++j;
							myQueries.push_back(new Predicate(QUERIES, queryStrings));
							queryStrings.clear();
						}
						leadID = true;
					}
				}
				else if (myTokens.at(j)->getTokenType() == COMMA)
				{
					if (parCounter)
					{
						dataOSS << myTokens.at(j)->getString();
					}
				}
				else
				{
					dataOSS << myTokens.at(j)->getString();
				}
			}
			++j;
			if (myTokens.at(j)->getTokenType() == MEOF)
			{
				break;
			}
		}
	}

	void toString()
	{
		cout << "Schemes(" << mySchemes.size() << "):" << endl;
		for (unsigned int k = 0; k < mySchemes.size(); ++k)
		{
			cout << mySchemes.at(k)->toString() << endl;
		}
		cout << "Facts(" << myFacts.size() << "):" << endl;
		for (unsigned int k = 0; k < myFacts.size(); ++k)
		{
			cout << myFacts.at(k)->toString() << endl;
		}
		cout << "Rules(" << myRules.size() << "):" << endl;
		for (unsigned int k = 0; k < myRules.size(); ++k)
		{
			cout << myRules.at(k)->toString() << endl;
		}
		cout << "Queries(" << myQueries.size() << "):" << endl;
		for (unsigned int k = 0; k < myQueries.size(); ++k)
		{
			cout << myQueries.at(k)->toString() << endl;
		}
	}

	void printDomain()
	{
		cout << "Domain(" << myDomain.size() << "):" << endl;
		bool keepGoing = true;
		//unsigned int iterations = 0;
		while (keepGoing && (myDomain.size() > 1))
		{
			//cout << ++iterations << endl;
			keepGoing = false;
			for (unsigned int k = 0; k < myDomain.size() - 1; ++k)
			{
				for (unsigned int l = 0; l < myDomain.at(k).length(); ++l)
				{
					if (myDomain.at(k).at(l) < myDomain.at(k + 1).at(l))
					{
						break;
					}
					if (myDomain.at(k).at(l) > myDomain.at(k + 1).at(l))
					{
						string temp = myDomain.at(k);
						myDomain.at(k) = myDomain.at(k + 1);
						myDomain.at(k + 1) = temp;
						keepGoing = true;
						break;
					}
				}
			}
		}
		for (unsigned int k = 0; k < myDomain.size(); ++k)
		{
			cout << "  " << myDomain.at(k) << endl;
		}
	}
	vector<Predicate*> getSchemes()
	{
		return mySchemes;
	}
	vector<Predicate*> getFacts()
	{
		return myFacts;
	}
	vector<Rule*> getRules()
	{
		return myRules;
	}
	vector<Predicate*> getQueries()
	{
		return myQueries;
	}
};

#endif