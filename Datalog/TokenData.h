#ifndef TOKEN_DATA_H
#define TOKEN_DATA_H

#include "TokenEnum.h"

class TokenData
{
private:
	Token tokenType;
	string asShown;
	int onLine;
public:
	TokenData(Token typeIn, string stringIn, int lineIn)
	{
		tokenType = typeIn;
		asShown = stringIn;
		onLine = lineIn;
	}
	void setTokenType(Token typeIn)
	{
		tokenType = typeIn;
	}
	Token getTokenType()
	{
		return tokenType;
	}
	void getString(string stringIn)
	{
		asShown = stringIn;
	}
	string getString()
	{
		return asShown;
	}
	void setOnLine(int lineIn)
	{
		onLine = lineIn;
	}
	int getOnLine()
	{
		return onLine;
	}
	string toString()
	{
		ostringstream stringOutOSS;
		stringOutOSS << "(" << toEnumString(tokenType) << ",\"" << asShown << "\"," << onLine << ")";
		return stringOutOSS.str();
	}
};

#endif