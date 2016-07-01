#ifndef LEXER_H
#define LEXER_H

#include <fstream>	
#include <string>
#include "Token.h"

class Lexer
{
public:
	Lexer(std::string regex);

	Token						GetNextToken();

private:
	void						Error(char ch);

	std::string					regex_;
	std::string					buffer_;
	std::string::size_type		index_ = 0;
	bool						error_ = false;
};

#endif