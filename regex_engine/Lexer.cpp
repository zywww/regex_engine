#include <string>
#include <iostream>
#include <cctype>
#include "Lexer.h"

using std::string;
using std::cout;
using std::endl;

enum class State
{
	START,
	BACKSLASH,
	INTEGER
};

Lexer::Lexer(string regex) : regex_(regex)
{
}

Token Lexer::GetNextToken()
{
	State state = State::START;
	
	while (index_ < regex_.length())
	{
		char ch = regex_[index_++];
		switch (state)
		{
		case State::START:
			switch (ch)
			{
			case '!':case '"':case '#':case '$':case '%':case '&':case '\'':case ',':case '/':
			case ':':case ';':case '<':case '=':case '>':case '@':case '_': case '`':case '~':
				return Token(TokenType::SIMPLE_CHAR, string() + ch);
			case '(': return Token(TokenType::LP, string() + ch);			// TODO 用 lambada 减少代码 
			case ')': return Token(TokenType::RP, string() + ch); 
			case '*': return Token(TokenType::ZERO_OR_MORE, string() + ch); 
			case '+': return Token(TokenType::ONE_OR_MORE, string() + ch); 
			case '-': return Token(TokenType::HYPHEN, string() + ch);
			case '.': return Token(TokenType::ANY, string() + ch); 
			case '?': return Token(TokenType::ZERO_OR_ONE, string() + ch); 
			case '[': return Token(TokenType::LBRACKET, string() + ch); 
			case ']': return Token(TokenType::RBRACKET, string() + ch);
			case '^': return Token(TokenType::NEGATE, string() + ch);
			case '{': return Token(TokenType::LBRACE, string() + ch);
			case '|': return Token(TokenType::OR, string() + ch);
			case '}': return Token(TokenType::RBRACE, string() + ch);
			case '\\': state = State::BACKSLASH; break;
			default:
				if (std::isalnum(ch))
					return Token(TokenType::SIMPLE_CHAR, string() + ch);
				else
					Error(ch);
			}
			break;
		case State::BACKSLASH:
			switch (ch)
			{
			case 't': return Token(TokenType::TAB, string("\\") + ch);
			case 'n': return Token(TokenType::NEWLINE, string("\\") + ch);
			case 'd': return Token(TokenType::DIGIT, string("\\") + ch);
			case 'D': return Token(TokenType::NOT_DIGIT, string("\\") + ch);
			case 's': return Token(TokenType::SPACE, string("\\") + ch);
			case 'S': return Token(TokenType::NOT_SPACE, string("\\") + ch);
			case 'w': return Token(TokenType::WORD, string("\\") + ch);
			case 'W': return Token(TokenType::NOT_WORD, string("\\") + ch);
			default: return Token(TokenType::SIMPLE_CHAR, string() + ch);
			}
			break;
		default:
			Error(ch);
		}
	}

	if (state == State::BACKSLASH)
	{
		error_ = true;
		cout << "空的转义字符" << endl;
	}
	return Token(TokenType::END, "\0");
}

void Lexer::Error(char ch)
{
	error_ = true;
	cout << "错误的单词 '" << ch << "'" << endl;
}

