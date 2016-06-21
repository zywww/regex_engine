#ifndef AST_H
#define AST_H

#include <utility>	
#include "Nfa.h"

using StatePtrPair = std::pair<NfaState*, NfaState*>;

class AstNode
{
public:
	virtual void print();
	virtual StatePtrPair constructNFA();
};

class AstFactor : public AstNode
{
public:
	AstFactor(char ch);
	
	void print();

	StatePtrPair constructNFA();

private:
	char		ch_;
};

class AstOR : public AstNode
{
public:
	AstOR(AstNode *leftNode, AstNode *rightNode);

	void print();

	StatePtrPair constructNFA();

private:
	AstNode		*leftNode_;
	AstNode		*rightNode_;
};

class AstConcat : public AstNode
{
public:
	AstConcat(AstNode *leftNode, AstNode *rightNode);

	void print();

	StatePtrPair constructNFA();

private:
	AstNode		*leftNode_;
	AstNode		*rightNode_;
};

class AstStar : public AstNode
{
public:
	AstStar(AstNode *node);

	void print();

	StatePtrPair constructNFA();

private:
	AstNode		*node_;
};

#endif