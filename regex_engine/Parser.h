#ifndef PARSER_H
#define PARSER_H

#include <utility>
#include <set>
#include "Lexer.h"
#include "Ast.h"

class Parser
{
public:
	Parser(const std::string &regex);

	void					Parse();

private:
	Lexer					lex_;
	Token					token_;
	bool					error_ = false;

	void					Error(const std::string &info);
	void					GetNextToken();
	bool					Match(TokenType type);

	ASTNode*				Regex();
	ASTNode*				Term();
	ASTNode*				Factor();
	ASTNode*				Atom();
	std::pair<int, int>		Repeat();
	std::set<char>				Character();
	ASTNode*				Charclass(bool negate);
	int						Digit();
	std::set<char>				Charrange();

};

#endif