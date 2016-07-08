#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser
{
public:
	Parser(const std::string &regex);

	void		Parse();

private:
	Lexer		lex_;
	Token		token_;
	bool		error_ = false;

	void		Error(const std::string &info);
	void		GetNextToken();
	bool		Match(TokenType type);

	void		Regex();
	void		Term();
	void		Factor();
	void		Atom();
	void		Repeat();
	void		Character();
	void		Charclass();
	int			Digit();
	void		Charrange();

};

#endif