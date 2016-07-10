//#include <iostream>
//#include "Ast.h"
//
//using std::endl;
//using std::cout;
//using std::make_pair;
//
//void AstNode::print()
//{
//
//}
//StatePtrPair AstNode::constructNFA()
//{
//	return make_pair(nullptr, nullptr);
//}
//
//// Class AstNode End
//
//AstFactor::AstFactor(char ch) : ch_(ch)
//{
//}
//
//void AstFactor::print()
//{
//	cout << ch_ << endl;
//}
//
//StatePtrPair AstFactor::constructNFA()
//{
//	auto start = new NfaState();
//	auto end = new NfaState();
//	auto edge = new NfaEdge(start, end, ch_);
//
//	return make_pair(start, end);
//}
//
// Class AstFactor End
//
//AstOR::AstOR(AstNode *leftNode, AstNode *rightNode)
//	: leftNode_(leftNode), rightNode_(rightNode)
//{
//}
//
//void AstOR::print()
//{
//	if (leftNode_)
//		leftNode_->print();
//	cout << "or" << endl;
//	if (rightNode_)
//		rightNode_->print();
//}
//
//StatePtrPair AstOR::constructNFA()
//{
//	auto left = leftNode_->constructNFA();
//	auto right = rightNode_->constructNFA();
//
//	auto start = new NfaState();
//	auto end = new NfaState();
//
//	auto startToLeft = new NfaEdge(start, left.first, '\0');
//	auto startToRight = new NfaEdge(start, right.first, '\0');
//	auto leftToEnd = new NfaEdge(left.second, end, '\0');
//	auto rightToEnd = new NfaEdge(right.second, end, '\0');
//
//	return make_pair(start, end);
//}
//
// Class AstOR End
//
//AstConcat::AstConcat(AstNode *leftNode, AstNode *rightNode)
//	: leftNode_(leftNode), rightNode_(rightNode)
//{
//}
//
//void AstConcat::print()
//{
//	if (leftNode_)
//		leftNode_->print();
//	cout << "cat" << endl;
//	if (rightNode_)
//		rightNode_->print();
//}
//
//StatePtrPair AstConcat::constructNFA()
//{
//	auto left = leftNode_->constructNFA();
//	auto right = rightNode_->constructNFA();
//
//	for (auto edge : right.first->outEdges_)
//	{
//		edge->startState_ = left.second;
//		left.second->outEdges_.push_back(edge);
//	}
//	
//	return make_pair(left.first, right.second);
//}
//
// Class AstConcat End
//
//AstStar::AstStar(AstNode *node) : node_(node)
//{
//}
//
//void AstStar::print()
//{
//	if (node_)
//		node_->print();
//	cout << '*' << endl;
//}
//
//StatePtrPair AstStar::constructNFA()
//{
//	auto node = node_->constructNFA();
//	auto start = new NfaState();
//	auto end = new NfaState();
//
//	auto startToNode = new NfaEdge(start, node.first, '\0');
//	auto startToEnd = new NfaEdge(start, end, '\0');
//	auto nodeToNode = new NfaEdge(node.second, node.first, '\0');
//	auto nodeToEnd = new NfaEdge(node.second, end, '\0');
//
//	return make_pair(start, end);
//}
//
// Class AstStar End

#include <iostream>
#include "Ast.h"

using std::cout;
using std::endl;

ASTOR::ASTOR(ASTNode *leftNode, ASTNode *rightNode)
	: leftNode_(leftNode), rightNode_(rightNode)
{
}

void ASTOR::Print()
{
	if (leftNode_)
		leftNode_->Print();
	cout << "or" << endl;
	if (rightNode_)
		rightNode_->Print();
}

StatePtrPair ASTOR::ConstructNFA()
{

}

// Class ASTOR End

ASTConcat::ASTConcat(ASTNode * leftNode, ASTNode *rightNode)
	: leftNode_(leftNode), rightNode_(rightNode)
{
}
void ASTConcat::Print()
{
	if (leftNode_)
		leftNode_->Print();
	cout << "cat" << endl;
	if (rightNode_)
		rightNode_->Print();
}

StatePtrPair ASTConcat::ConstructNFA()
{

}

// Class ASTConcat End

ASTRepeat::ASTRepeat(ASTNode *node, int min, int max)
	: node_(node), min_(min), max_(max)
{
}

void ASTRepeat::Print()
{
	if (node_)
		node_->Print();
	cout << "重复 " << min_ << "次到 " << max_ << "次" << endl;
}

StatePtrPair ASTRepeat::ConstructNFA()
{

}

// Class ASTRepeat End

ASTFactor::ASTFactor(char ch) : ch_(ch)
{
}

void ASTFactor::Print()
{
	cout << ch_ << endl;
}

StatePtrPair ASTFactor::ConstructNFA()
{

}

// Class SATFactor End