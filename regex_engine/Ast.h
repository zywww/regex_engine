#ifndef AST_H
#define AST_H

class AstNode
{
public:
	virtual void print() {}
};

class AstFactor : public AstNode
{
public:
	AstFactor(char ch);
	
	void print();

private:
	char		ch_;
};

class AstOR : public AstNode
{
public:
	AstOR(AstNode *leftNode, AstNode *rightNode);

	void print();

private:
	AstNode		*leftNode_;
	AstNode		*rightNode_;
};

class AstConcat : public AstNode
{
public:
	AstConcat(AstNode *leftNode, AstNode *rightNode);

	void print();

private:
	AstNode		*leftNode_;
	AstNode		*rightNode_;
};

class AstStar : public AstNode
{
public:
	AstStar(AstNode *node);

	void print();

private:
	AstNode		*node_;
};

#endif