#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
	SIMPLE_CHAR,
	
	LP,				// (   非简单字符，转义之后成为简单字符
	RP,				// )
	ZERO_OR_MORE,	// *
	ONE_OR_MORE,	// +
	ZERO_OR_ONE,	// ?
	HYPHEN,			// -   连接号
	ANY,			// .   任意字符
	LBRACKET,		// [
	RBRACKET,		// ]
	BACKSLASH,		// \\  反斜杠
	NEGATE,			// ^   取反
	LBRACE,			// {
	RBRACE,			// }
	OR,				// |



	
	TAB,			// \t
	NEWLINE,		// \n
	DIGIT,			// \d  ==  [0-9]
	NOT_DIGIT,		// \D  ==  [^0-9]
	SPACE,			// \s  ==  [ \t\n]
	NOT_SPACE,		// \S  ==  [^ \t\n]
	WORD,			// \w  ==  [a-zA-Z0-9_]
	NOT_WORD,		// \W  ==  [^a-zA-Z0-9_]

	INTEGER,		// 整数，只用于 regex{min, max}

	END
};

struct Token
{
	Token(TokenType type, std::string lexeme);

	TokenType		type_;
	std::string		lexeme_;
};

#endif
