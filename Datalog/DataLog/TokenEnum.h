#ifndef TOKEN_ENUM_H
#define TOKEN_ENUM_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

enum Token
{
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES,
	FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, MEOF
};

string toEnumString(Token t)
{
	switch (t)
	{
	case COMMA:
		return "COMMA";
	case PERIOD:
		return "PERIOD";
	case Q_MARK:
		return "Q_MARK";
	case LEFT_PAREN:
		return "LEFT_PAREN";
	case RIGHT_PAREN:
		return "RIGHT_PAREN";
	case COLON:
		return "COLON";
	case COLON_DASH:
		return "COLON_DASH";
	case MULTIPLY:
		return "MULTIPLY";
	case ADD:
		return "ADD";
	case SCHEMES:
		return "SCHEMES";
	case FACTS:
		return "FACTS";
	case RULES:
		return "RULES";
	case QUERIES:
		return "QUERIES";
	case ID:
		return "ID";
	case STRING:
		return "STRING";
	case COMMENT:
		return "COMMENT";
	case WHITESPACE:
		return "WHITESPACE";
	case UNDEFINED:
		return "UNDEFINED";
	case MEOF:
		return "EOF";
	default:
		break;
	}
	return "ERROR001";
}

#endif