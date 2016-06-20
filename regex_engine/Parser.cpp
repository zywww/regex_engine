#include <string>
#include <iostream>
#include <cctype>
#include "Parser.h"

using std::string;
using std::cout;
using std::endl;

Parser::Parser(string regualrExpr) : regex_(regualrExpr), ch_(regex_[0])
{
	regex_ += '\0';
}

void Parser::Parse()
{
	Regex();
	if (error_)
		cout << "regex syntex error!" << endl;
	else
		cout << "regex syntex right." << endl;
}

void Parser::Regex()
{
	Concat();
	while (Match('|') && !IsEnd())
	{
		Read();
		Concat();
	}

	if (index_ < regex_.length())
		error_ = false;
}

void Parser::Concat()
{
	Element();
	while (std::isalnum(ch_) || Match('('))
		Element();
}

void Parser::Element()
{
	Factor();
	if (Match('*'))
		Read();
}

void Parser::Factor()
{
	if (Match('('))
	{
		Read();
		Regex();
		MatchAndRead(')');
	}
	else if (std::isalnum(ch_))
	{
			Read();
	}
	else
	{
		error_ = true;
		Read();
	}
}

bool Parser::IsEnd()
{
	if (index_ >= regex_.length())
		return true;
	else
		return false;
}

void Parser::Read()
{
	ch_ = regex_[++index_];
}

bool Parser::Match(char ch)
{
	if (ch_ == ch)
		return true;
	else
		return false;
}

bool Parser::MatchAndRead(char ch)
{
	if (ch_ == ch)
	{
		Read();
		return true;
	}
	else
	{
		error_ = true;
		Read();
		return false;
	}
}