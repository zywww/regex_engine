#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
#include "Parser.h"
#include "Nfa.h"

using std::string;
using std::cout;
using std::endl;

Parser::Parser(string regualrExpr, std::string matchContent) 
	: regex_(regualrExpr), matchContent_(matchContent), ch_(regex_[0])
{
}

void Parser::Parse()
{
	AstNode *astRoot = Regex();
	
	
	if (index_ < regex_.length())
		error_ = true;

	if (error_)
		cout << "regex syntex error!" << endl;
	else
	{
		auto nfa = astRoot->constructNFA();
		nfa.second->accept = true;
		bool accept = RunNfa(nfa.first, matchContent_);

		cout << "regex syntex right." << endl;
		if (accept)
			cout << "match" << endl;
		else
			cout << "not match" << endl;
		//astRoot->print();
	}
		
}

AstNode* Parser::Regex()
{
	AstNode *node = Concat();
	while (Match('|'))
	{
		Read();
		node = new AstOR(node, Concat());
	}
	return node;
}

AstNode* Parser::Concat()
{
	AstNode *node = Element();
	while (std::isalnum(ch_) || Match('('))
		node = new AstConcat(node, Element());
	return node;
}

AstNode* Parser::Element()
{
	AstNode *node = Factor();
	if (Match('*'))
	{
		node = new AstStar(node);
		Read();
	}
	return node;
}

AstNode* Parser::Factor()
{
	AstNode * node = nullptr;
	if (Match('('))
	{
		Read();
		node = Regex();
		if (Match(')'))
		{
			Read();
		}
		else
		{
			assert(false && "缺少 ')'");
		}
	}
	else if (std::isalnum(ch_))
	{
		node = new AstFactor(ch_);
		Read();
	}
	else
	{
		assert(false && "缺少因子");
		error_ = true;
		Read();
	}
	return node;
}

void Parser::Read()
{
	ch_ = regex_[++index_];
	if (index_ >= regex_.length())
		ch_ = '\0';
}

bool Parser::Match(char ch)
{
	if (ch_ == ch)
		return true;
	else
		return false;
}

//
//bool Parser::MatchAndRead(char ch)
//{
//	if (ch_ == ch)
//	{
//		Read();
//		return true;
//	}
//	else
//	{
//		// assert(true && "缺少")
//		error_ = true;
//		Read();
//		return false;
//	}
//}