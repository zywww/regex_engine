#include <set>
#include <iostream>
#include <cctype>
#include "Parser.h"	


using std::endl;
using std::cout;
using std::string;
using std::pair;
using std::set;

Parser::Parser(const std::string &regex, const std::string &matchContent) 
	: lex_(regex), token_(TokenType::END, "\0"), matchContent_(matchContent)
{
	GetNextToken();
}

void Parser::GetNextToken()
{
	token_ = lex_.GetNextToken();
}

bool Parser::Match(TokenType type)
{
	return token_.type_ == type;
}


void Parser::Error(const string &info)
{
	cout << info << endl;
	error_ = true;
	GetNextToken();
}

void Parser::Parse()
{
	ASTNode* root = Regex();
	
	if (!Match(TokenType::END))
		error_ = true;

	if (error_)
	{
		cout << "正则表达式语法错误" << endl;
	}
	else
	{
		cout << "正则表达式语法正确" << endl;
		if (root)
		{
			auto nodePair = root->ConstructNFA();
			nodePair.second->accept = true;
			if (RunNFA(nodePair.first, matchContent_))
				cout << "匹配成功" << endl;
			else
				cout << "匹配失败" << endl;
		}
		
	}
	
}

ASTNode* Parser::Regex()
{
	ASTNode* node = Term();
	while (Match(TokenType::OR))
	{
		GetNextToken();
		node = new ASTOR(node, Term());
	}
	
	return node;
}
 
ASTNode* Parser::Term()
{
	ASTNode* node = Factor();

	while (true)
	{
		bool into = false;
		switch (token_.type_)		// 如果下一个 token 属于 factor 则调用 factor，否则 term 调用结束
		{
		case TokenType::LBRACKET:
		case TokenType::LP:
		case TokenType::SIMPLE_CHAR:
		case TokenType::TAB:
		case TokenType::NEWLINE:
		case TokenType::DIGIT:
		case TokenType::NOT_DIGIT:
		case TokenType::SPACE:
		case TokenType::NOT_SPACE:
		case TokenType::WORD:
		case TokenType::NOT_WORD:
		case TokenType::ANY:
			node = new ASTConcat(node, Factor());
			into = true;
			break;
		default:
			into = false;
			break;
		}
		if (!into)
			break;
	}

	return node;
}

ASTNode* Parser::Factor()
{
	ASTNode* node = Atom();
	std::pair<int, int> minAndMax{ 1,1 };
	switch (token_.type_)
	{
	case TokenType::LBRACE:
	case TokenType::ZERO_OR_MORE:
	case TokenType::ONE_OR_MORE:
	case TokenType::ZERO_OR_ONE:
		minAndMax = Repeat();
		break;
	default:
		return node;		// 若没有重复范围，直接返回 node
	}
	
	//if (minAndMax.first == 0 && minAndMax.second == -1)				// 如 ab*
	//{
	//	return new ASTStar(node);
	//}
	//else if (minAndMax.first == 1 && minAndMax.second == -1)		// 如 ab+
	//{
	//	return new ASTConcat(node, new ASTStar(node));
	//}
	//else if (minAndMax.first == 0 && minAndMax.second == 1)			// 如 ab?
	//{
	//	return new ASTOR(new ASTFactor('\0'), node);
	//}
	//else
	//{
	//	ASTNode* resultPart1 = new ASTFactor('\0');
	//	for (int i = 1; i <= minAndMax.first; ++i)
	//		resultPart1 = new ASTConcat(resultPart1, node);

	//	if (minAndMax.second == -1)
	//	{
	//		return new ASTConcat(resultPart1, new ASTStar(node));
	//	}

	//	
	//	ASTNode* resultPart2 = new ASTFactor('\0');
	//	for (int i = 1; i <= minAndMax.second - minAndMax.first; ++i)
	//	{
	//		ASTNode* temp = new ASTFactor('\0');
	//		for (int j = 1; j <= i; ++j)
	//		{
	//			temp = new ASTConcat(temp, node);
	//		}
	//		resultPart2 = new ASTOR(resultPart2, temp);
	//	}
	//	
	//	return new ASTConcat(resultPart1, resultPart2);
	//}

	
	// 提取公因子的第一部分
	ASTNode* resultPart1 = new ASTFactor('\0');
	for (int i = 1; i <= minAndMax.first; ++i)
		resultPart1 = new ASTConcat(resultPart1, node);

	ASTNode* resultPart2 = new ASTFactor('\0');
	if (minAndMax.second == -1)
	{
		resultPart2 = new ASTStar(node);
	}
	else
	{
		for (int i = 1; i <= minAndMax.second - minAndMax.first; ++i)
		{
			ASTNode* temp = new ASTFactor('\0');
			for (int j = 1; j <= i; ++j)
			{
				temp = new ASTConcat(temp, node);
			}
			resultPart2 = new ASTOR(resultPart2, temp);
		}
	}

	return new ASTConcat(resultPart1, resultPart2);
}

ASTNode* Parser::Atom()
{
	ASTNode* node = nullptr;
	bool negate = false;
	set<char> range;
	switch (token_.type_)
	{
	case TokenType::LP: 
		GetNextToken(); 
		node = Regex(); 
		if (!Match(TokenType::RP)) Error("缺少右括号 ')'");
		else GetNextToken();
		break;

	case TokenType::LBRACKET:
		GetNextToken();
		if (Match(TokenType::NEGATE))
		{
			GetNextToken();
			negate = true;
		}
		node = Charclass(negate);
		if (!Match(TokenType::RBRACKET))
			Error("缺少 ']'");
		else
			GetNextToken();
		break;

	case TokenType::ANY:
		node = new ASTFactor(' ');
		for (char ch = '!'; ch <= '~'; ++ch)
			node = new ASTOR(node, new ASTFactor(ch));
		GetNextToken();
		break;

	default:
		range = Character();
		for (auto ch : range)
			node = new ASTOR(node, new ASTFactor(ch));
	}
	
	return node;
}

std::pair<int, int> Parser::Repeat()
{
	int min = -1;
	int max = -1;
	switch (token_.type_)
	{
	case TokenType::LBRACE:
		GetNextToken();
		min = Digit();
		if (Match(TokenType::SIMPLE_CHAR) && token_.lexeme_ == ",")
		{
			GetNextToken();
			if (Match(TokenType::RBRACE))
			{
				GetNextToken();
			}
			else
			{
				max = Digit();
				if (min > max)
				{
					Error("{ } 中的范围错误");
				}
				if (!Match(TokenType::RBRACE))
					Error("缺少 '}'");
				else
					GetNextToken();
			}
		}
		else if (Match(TokenType::RBRACE))
		{
			max = min;
			GetNextToken();
		}
		else
		{
			Error("'{' '}'内语法错误");
		}
		break;

	case TokenType::ZERO_OR_MORE:
		min = 0;
		GetNextToken();
		break;

	case TokenType::ONE_OR_MORE:
		min = 1;
		GetNextToken();
		break;

	case TokenType::ZERO_OR_ONE:
		min = 0;
		max = 1;
		GetNextToken();
		break;
	default:
		Error(string("错误的符号 '") + token_.lexeme_ + '\'');
	}
	return std::pair<int, int>{min, max};
}

set<char> Parser::Character()
{
	const auto type = token_.type_;
	set<char> chSet;

	switch (type)
	{
	case TokenType::SIMPLE_CHAR:
		chSet.insert(token_.lexeme_[0]);
		GetNextToken(); 	
		break;

	case TokenType::TAB:
		chSet.insert('\t');
		GetNextToken();
		break;

	case TokenType::NEWLINE:
		chSet.insert('\n');
		GetNextToken();
		break;

	case TokenType::DIGIT:
		for (char ch = '0'; ch <= '9'; ++ch)
			chSet.insert(ch);
		GetNextToken();
		break;

	case TokenType::NOT_DIGIT:
		for (char ch = ' '; ch <= '~'; ++ch)
			if (!std::isdigit(ch))
				chSet.insert(ch);
		GetNextToken();
		break;

	case TokenType::SPACE:
		chSet.insert(' ');
		GetNextToken();
		break;

	case TokenType::NOT_SPACE:
		for (char ch = ' ' + 1; ch <= '~'; ++ch)
			chSet.insert(ch);
		GetNextToken();;
		break;

	case TokenType::WORD:
		for (char ch = ' '; ch <= '~'; ++ch)
			if (std::isalnum(ch) || ch == '_')
				chSet.insert(ch);
		GetNextToken();
		break;

	case TokenType::NOT_WORD:
		for (char ch = ' '; ch <= '~'; ++ch)
			if (!(std::isalnum(ch) || ch == '_'))
				chSet.insert(ch);
		GetNextToken();
		break;
	default:
		Error("错误的因子");
	}
	
	return chSet;
}

ASTNode* Parser::Charclass(bool negate)
{
	set<char> chSet;
	set<char> negateCHSet;
	while (!Match(TokenType::RBRACKET))
	{
		set<char> range = Charrange();
		for (auto ch : range)
			chSet.insert(ch);
	}
	// 如果集合为空可以吗

	ASTNode *node = nullptr;

	if (negate)
	{
		for (char ch = ' '; ch <= '~'; ++ch)
			if (chSet.find(ch) == chSet.end())
				negateCHSet.insert(ch);
		for (auto ch : negateCHSet)
			node = new ASTOR(node, new ASTFactor(ch));
	}
	else
	{
		for (auto ch : chSet)
			node = new ASTOR(node, new ASTFactor(ch));
	}

	return node;	// ASTOR 中的子节点可能为 nullptr
}

set<char> Parser::Charrange()
{
	set<char> begin = Character();
	set<char> end;
	bool range = false;
	if (Match(TokenType::HYPHEN))
	{
		GetNextToken();
		end = Character();
		range = true;
	}

	if (range)
	{
		if (begin.size() != 1 || end.size() != 1)
		{
			Error("字符集合 [] 中范围错误");
			return begin;
		}

		if (*begin.begin() > *end.begin())
		{
			Error("字符集合 [] 中范围错误");
			return begin;
		}

		set<char> range;
		for (char ch = *begin.begin(); ch <= *end.begin(); ++ch)
			range.insert(ch);	
		return range;
	}
	else
	{
		return begin;
	}
}

int Parser::Digit()
{
	string buffer;
	while (Match(TokenType::SIMPLE_CHAR) && std::isdigit(token_.lexeme_[0]))
	{
		buffer += token_.lexeme_[0];
		GetNextToken();
	}
	if (buffer.empty())
		Error("缺少重复次数");
	else
		return std::stoi(buffer);
	
	return 0;
}
