#include "DatalogProgram.h"
#include "Database.h"

bool fileError(int argc);
void generateTokens(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& i);
unsigned int s0(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter);
unsigned int s1(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString);
unsigned int s2(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString);
unsigned int s3(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString);
unsigned int s4(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine);
unsigned int s5(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine);
unsigned int s6(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine);
unsigned int s7(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine);
unsigned int s8(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString);
unsigned int s9(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine);
unsigned int s10(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine);

int main(int argc, char* argv[])
{
	if (fileError(argc))
	{
		cout << "NO FILE ADDED" << endl;
		return 0;
	}

	ifstream dataIn(argv[1]);
	vector<string> inputStrings;
	vector<TokenData*> myTokens;
	while (!dataIn.eof())
	{
		string inputLine;
		getline(dataIn, inputLine);
		inputStrings.push_back(inputLine);
	}
	for (unsigned int i = 0; i < inputStrings.size(); ++i)
	{
		generateTokens(inputStrings, myTokens, i);
	}
	myTokens.push_back(new TokenData(MEOF, "", static_cast<unsigned int>(inputStrings.size())));

	DatalogProgram checkGrammar(myTokens);
	if (checkGrammar.isSyntaxValid())
	{
		checkGrammar.generateLists();
		Database myData(checkGrammar.getSchemes(), checkGrammar.getFacts(), checkGrammar.getRules(),
			checkGrammar.getQueries());
		myData.populateRelations();
		myData.answerQueries();
	}
	for (unsigned int i = 0; i < myTokens.size(); ++i)
	{
		delete myTokens.at(i);
	}
	return 0;
}

bool fileError(int argc)
{
	if (argc < 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void generateTokens(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter)
{
	if (inputStrings.at(lineIter) == "")
	{
		return;
	}
	else
	{
		unsigned int charsLeft = 0;
		while (inputStrings.at(lineIter).size() > charsLeft)
		{
			charsLeft = s0(inputStrings, myTokens, lineIter);
		}
	}
}

unsigned int s0(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter)
{
	unsigned int charIter = 0;
	char currentChar = inputStrings.at(lineIter).at(charIter);
	switch (currentChar)
	{
	case ',':
		myTokens.push_back(new TokenData(COMMA, ",", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case '.':
		myTokens.push_back(new TokenData(PERIOD, ".", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case '?':
		myTokens.push_back(new TokenData(Q_MARK, "?", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case '(':
		myTokens.push_back(new TokenData(LEFT_PAREN, "(", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case ')':
		myTokens.push_back(new TokenData(RIGHT_PAREN, ")", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case ':':
		++charIter;
		if (charIter >= inputStrings.at(lineIter).size())
		{
			myTokens.push_back(new TokenData(COLON, ":", lineIter + 1));
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
		}
		else if (inputStrings.at(lineIter).at(charIter) == '-')
		{
			myTokens.push_back(new TokenData(COLON_DASH, ":-", lineIter + 1));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
		}
		else
		{
			myTokens.push_back(new TokenData(COLON, ":", lineIter + 1));
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0; // moved breaks to bottom
		}
		break;
	case '*':
		myTokens.push_back(new TokenData(MULTIPLY, "*", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case '+':
		myTokens.push_back(new TokenData(ADD, "+", lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case ' ':
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case '\t':
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		break;
	case '\'':
		if (true)
		{
			// not sure why I had to do this, but it kept throwing errors otherwise
			string maybeString = "";
			maybeString.push_back(currentChar);
			charIter = s3(inputStrings, myTokens, lineIter, charIter, maybeString);
		}
		break;
	case '#':
		++charIter;
		if (true) // still not sure why I had to do this but here we are
		{ // apparently it has something to do with switch statements? Either way, weird
			string maybeString = "";
			maybeString.push_back(currentChar);
			if (charIter >= inputStrings.at(lineIter).size())
			{
				maybeString.push_back(currentChar);
				myTokens.push_back(new TokenData(UNDEFINED, maybeString, lineIter + 1));
				inputStrings.at(lineIter).erase(0, charIter);
				charIter = 0;
			}
			else if (inputStrings.at(lineIter).at(charIter) == '|') // MULTI-LINE comment
			{
				currentChar = inputStrings.at(lineIter).at(charIter);
				maybeString.push_back(currentChar);
				const unsigned int originalLine = lineIter + 1;
				charIter = s9(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
			}
			else
			{
				currentChar = inputStrings.at(lineIter).at(charIter);
				maybeString.push_back(currentChar);
				charIter = s8(inputStrings, myTokens, lineIter, charIter, maybeString); // should be 0
			}
		}
		break;
	default:
		if (isalpha(currentChar))
		{
			string maybeString = "";
			maybeString.push_back(currentChar);
			charIter = s1(inputStrings, myTokens, lineIter, charIter, maybeString); // should be 0
		}
		else
		{
			string tempString = "";
			tempString.push_back(currentChar);
			myTokens.push_back(new TokenData(UNDEFINED, tempString, lineIter + 1));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
		}
	}
	return charIter;
}

unsigned int s1(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{
		return s2(inputStrings, myTokens, lineIter, charIter, maybeString);
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (isalnum(currentChar))
	{
		maybeString.push_back(currentChar);
		charIter = s1(inputStrings, myTokens, lineIter, charIter, maybeString);
	}
	else
	{
		return s2(inputStrings, myTokens, lineIter, charIter, maybeString);
	}
	return charIter;
}

unsigned int s2(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString)
{
	--charIter;
	if (maybeString == "Schemes")
	{
		myTokens.push_back(new TokenData(SCHEMES, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
	}
	else if (maybeString == "Facts")
	{
		myTokens.push_back(new TokenData(FACTS, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
	}
	else if (maybeString == "Rules")
	{
		myTokens.push_back(new TokenData(RULES, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
	}
	else if (maybeString == "Queries")
	{
		myTokens.push_back(new TokenData(QUERIES, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
	}
	else
	{
		myTokens.push_back(new TokenData(ID, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
	}
	return charIter;
}

unsigned int s3(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString)
{
	const unsigned int originalLine = lineIter + 1;
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{
		++lineIter;
		if (lineIter >= inputStrings.size())
		{ // undefined because no ' at end, and doesn't continue onto next line
			--lineIter; // might not work, see above
			myTokens.push_back(new TokenData(UNDEFINED, maybeString, originalLine));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
			return charIter;
		}
		else
		{
			charIter = -1; // -1 to compensate for ++charIter at beginning of s7, to start at 0
			maybeString.push_back('\n');
			return s7(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		}
		
		
		
		/*myTokens.push_back(new TokenData(UNDEFINED, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;*/ // UNLESS NEW LINE?
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '\'')
	{
		maybeString.push_back(currentChar);
		charIter = s4(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		//check for another - s4?
		/*maybeString.push_back(currentChar);
		charIter = s1(inputStrings, myTokens, lineIter, charIter, maybeString);*/
	}
	else
	{
		maybeString.push_back(currentChar);
		return s7(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		// FIX BELOW no recursino to s3
		// get string from between ''s
		//charIter = s3(inputStrings, myTokens, lineIter, charIter, maybeString);
	}
	return charIter;
}

unsigned int s4(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{ // push empty string
		myTokens.push_back(new TokenData(STRING, maybeString, originalLine));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '\'')
	{
		maybeString.push_back(currentChar);
		charIter = s5(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		//check for another - s4?
		/*maybeString.push_back(currentChar);
		charIter = s1(inputStrings, myTokens, lineIter, charIter, maybeString);*/
	}
	else
	{
		/*maybeString.push_back(currentChar);
		myTokens.push_back(new TokenData(UNDEFINED, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;*/
		myTokens.push_back(new TokenData(STRING, maybeString, originalLine));
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;
	}
	return charIter;
}

unsigned int s5(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{ // undefined, didn't end evenly
		++lineIter;
		if (lineIter >= inputStrings.size())
		{ // undefined because no ' at end, and doesn't continue onto next line
			--lineIter; // might not work, see above
			myTokens.push_back(new TokenData(UNDEFINED, maybeString, originalLine));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
			return charIter;
		}
		else
		{
			charIter = -1; // -1 to compensate for ++charIter at beginning of s7, to start at 0
			maybeString.push_back('\n');
			return s7(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		}
	  
	  
	  
	  
	  /*myTokens.push_back(new TokenData(UNDEFINED, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;*/ // UNLESS NEW LINE?
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '\'')
	{
		maybeString.push_back(currentChar);
		charIter = s6(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		//check for another - s4?
		/*maybeString.push_back(currentChar);
		charIter = s1(inputStrings, myTokens, lineIter, charIter, maybeString);*/
	}
	else
	{
		// FIXME, get string within FIXED?
		maybeString.push_back(currentChar);
		charIter = s7(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		
		/*myTokens.push_back(new TokenData(UNDEFINED, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;*/
	}
	return charIter;
}

unsigned int s6(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{ // push string
		myTokens.push_back(new TokenData(STRING, maybeString, originalLine));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '\'')
	{
		maybeString.push_back(currentChar);
		charIter = s5(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		//check for another - s4?
		/*maybeString.push_back(currentChar);
		charIter = s1(inputStrings, myTokens, lineIter, charIter, maybeString);*/
	}
	else
	{
		// finished string
		myTokens.push_back(new TokenData(STRING, maybeString, originalLine));
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;
	}
	return charIter;
}

unsigned int s7(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{ // unfinished string, undefined
		++lineIter;
		if (lineIter >= inputStrings.size())
		{ // undefined because no ' at end, and doesn't continue onto next line
			--lineIter; // might not work, see above
			myTokens.push_back(new TokenData(UNDEFINED, maybeString, originalLine));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
			return charIter;
		}
		else
		{
			charIter = -1; // -1 to compensate for ++charIter at beginning of s7, to start at 0
			maybeString.push_back('\n');
			return s7(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		}
	  
	  
	  
	  
		/*myTokens.push_back(new TokenData(UNDEFINED, maybeString, lineIter + 1));
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;*/ // UNLESS NEW LINE?
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '\'')
	{
		maybeString.push_back(currentChar);
		charIter = s6(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
	}
	else
	{
		maybeString.push_back(currentChar);
		return s7(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine); // get more letters
	}
	return charIter;
}

unsigned int s8(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size())
	{ // finished, push final comment
		//myTokens.push_back(new TokenData(COMMENT, maybeString, lineIter + 1)); //commented out for project 2
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;
	}
	else
	{
		char currentChar = inputStrings.at(lineIter).at(charIter);
		maybeString.push_back(currentChar);
		return s8(inputStrings, myTokens, lineIter, charIter, maybeString); // get more letters
	}
	return charIter;
}

unsigned int s9(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size()) // new line
	{
		++lineIter;
		if (lineIter >= inputStrings.size())
		{ // undefined because no"|#" before end of file
			--lineIter; // might not be right - added to prevent deletion of nonexistant line?
			myTokens.push_back(new TokenData(UNDEFINED, maybeString, originalLine));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
			return charIter;
		}
		else
		{ // multi-line comment continues onto next line
			charIter = -1; // -1 to compensate for ++charIter at beginning of s7, to start at 0
			maybeString.push_back('\n');
			return s9(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		}
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '|')
	{
		maybeString.push_back(inputStrings.at(lineIter).at(charIter));
		return s10(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine); // go check for #
	}
	else
	{
		maybeString.push_back(inputStrings.at(lineIter).at(charIter));
		return s9(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine); // get more letters
	}
	return charIter;
}

unsigned int s10(vector<string>& inputStrings, vector<TokenData*>& myTokens, unsigned int& lineIter,
	unsigned int& charIter, string& maybeString, const unsigned int originalLine)
{
	++charIter;
	if (charIter >= inputStrings.at(lineIter).size()) // new line
	{
		++lineIter;
		if (lineIter >= inputStrings.size())
		{ // undefined because no"|#" before end of file
			--lineIter; // might not work, see above
			myTokens.push_back(new TokenData(UNDEFINED, maybeString, originalLine));
			++charIter;
			inputStrings.at(lineIter).erase(0, charIter);
			charIter = 0;
			return charIter;
		}
		else
		{ // multi-line comment continues onto next line
			charIter = -1; // -1 to compensate for ++charIter at beginning of s7, to start at 0
			maybeString.push_back('\n');
			return s9(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine);
		}
	}
	char currentChar = inputStrings.at(lineIter).at(charIter);
	if (currentChar == '#')
	{ // finished, push final multi-line comment
		maybeString.push_back(currentChar);
		//myTokens.push_back(new TokenData(COMMENT, maybeString, originalLine)); //commented out for Project 2
		++charIter;
		inputStrings.at(lineIter).erase(0, charIter);
		charIter = 0;
		return charIter;
	}
	else
	{
		maybeString.push_back(inputStrings.at(lineIter).at(charIter));
		return s9(inputStrings, myTokens, lineIter, charIter, maybeString, originalLine); // get more letters
	}
	return charIter;
}