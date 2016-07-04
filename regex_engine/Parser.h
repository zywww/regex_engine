//#ifndef PARSER_H
//#define PARSER_H
//
//#include <string>
//#include "Ast.h"
//#include "Lexer.h"	
//
//class Parser
//{
//public:
//	Parser(std::string regualrExpr, std::string matchContent);
//
//	void		Parse();
//	AstNode*	Regex();
//	AstNode*	Concat();
//	AstNode*	Element();
//	AstNode*	Factor();
//
//
//private:
//	void	Read();					// 读取正则表达式中下个字符
//	bool	Match(char ch);			// 将当前字符与 ch 匹配
//	// bool	MatchAndRead(char ch);	// 将当前字符与 ch 匹配，若成功则读取下个字符，若失败，则 error_ 置为 true
//
//
//	std::string					regex_;
//	std::string					matchContent_;
//	bool						error_ = false;
//	std::string::size_type		index_ = 0;
//	char						ch_;
//};
//
//#endif

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