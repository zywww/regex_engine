#include <iostream>
#include "Ast.h"

using std::endl;
using std::cout;

AstFactor::AstFactor(char ch) : ch_(ch)
{
}

void AstFactor::print()
{
	cout << ch_ << endl;
}

// Class AstFactor End

AstOR::AstOR(AstNode *leftNode, AstNode *rightNode)
	: leftNode_(leftNode), rightNode_(rightNode)
{
}

void AstOR::print()
{
	if (leftNode_)
		leftNode_->print();
	cout << "or" << endl;
	if (rightNode_)
		rightNode_->print();
}

// Class AstOR End

AstConcat::AstConcat(AstNode *leftNode, AstNode *rightNode)
	: leftNode_(leftNode), rightNode_(rightNode)
{
}

void AstConcat::print()
{
	if (leftNode_)
		leftNode_->print();
	cout << "cat" << endl;
	if (rightNode_)
		rightNode_->print();
}

// Class AstConcat End

AstStar::AstStar(AstNode *node) : node_(node)
{
}

void AstStar::print()
{
	if (node_)
		node_->print();
	cout << '*' << endl;
}

// Class AstStar End