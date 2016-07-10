//#ifndef ast_h
//#define ast_h
//
//#include <utility>	
//#include "nfa.h"
//
//using stateptrpair = std::pair<nfastate*, nfastate*>;
//
//class ASTnode
//{
//public:
//	virtual void print();
//	virtual stateptrpair constructnfa();
//};
//
//class astfactor : public astnode
//{
//public:
//	astfactor(char ch);
//	
//	void print();
//
//	stateptrpair constructnfa();
//
//private:
//	char		ch_;
//};
//
//class astor : public astnode
//{
//public:
//	astor(astnode *leftnode, astnode *rightnode);
//
//	void print();
//
//	stateptrpair constructnfa();
//
//private:
//	astnode		*leftnode_;
//	astnode		*rightnode_;
//};
//
//class astconcat : public astnode
//{
//public:
//	astconcat(astnode *leftnode, astnode *rightnode);
//
//	void print();
//
//	stateptrpair constructnfa();
//
//private:
//	astnode		*leftnode_;
//	astnode		*rightnode_;
//};
//
//class aststar : public astnode
//{
//public:
//	aststar(astnode *node);
//
//	void print();
//
//	stateptrpair constructnfa();
//
//private:
//	astnode		*node_;
//};
//
//#endif
//

#ifndef AST_H
#define AST_H

#include <utility>	
#include "nfa.h"

using StatePtrPair = std::pair<NFAState*, NFAState*>;

class ASTNode
{
public:
	virtual void			Print();
	virtual StatePtrPair	ConstructNFA();

};


class ASTOR : public ASTNode
{
public:
	ASTOR(ASTNode *leftNode, ASTNode *rightNode);

	virtual void			Print();
	virtual StatePtrPair	ConstructNFA();

private:
	ASTNode					*leftNode_;
	ASTNode					*rightNode_;
};


class ASTConcat : public ASTNode
{
public:
	ASTConcat(ASTNode *leftNode, ASTNode *rightNode);

	virtual void			Print();
	virtual StatePtrPair	ConstructNFA();

private:
	ASTNode					*leftNode_;
	ASTNode					*rightNode_;
};


class ASTRepeat : public ASTNode
{
public:
	ASTRepeat(ASTNode *node, int min, int max);

	virtual void			Print();
	virtual StatePtrPair	ConstructNFA();

private:		
	ASTNode					*node_;
	int						min_;
	int						max_;
};


class ASTFactor : public ASTNode
{
public:
	ASTFactor(char ch);

	virtual void			Print();
	virtual StatePtrPair	ConstructNFA();

private:
	char					ch_;
};


#endif