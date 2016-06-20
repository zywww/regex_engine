#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser
{
public:
	Parser(std::string regualrExpr);

	void	Parse();
	void	Regex();
	void	Concat();
	void	Element();
	void	Factor();


private:
	bool	IsEnd();
	void	Read();					// 读取正则表达式中下个字符
	bool	Match(char ch);			// 将当前字符与 ch 匹配
	bool	MatchAndRead(char ch);	// 将当前字符与 ch 匹配，若成功则读取下个字符，若失败，则 error_ 置为 true


	std::string					regex_;
	bool						error_ = false;
	std::string::size_type		index_ = 0;
	char						ch_;
};

#endif