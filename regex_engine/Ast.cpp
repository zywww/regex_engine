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
using std::make_pair;

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
	if (leftNode_)
	{
		auto left = leftNode_->ConstructNFA();
		auto right = rightNode_->ConstructNFA();
		
		auto start = new NFAState();
		auto end = new NFAState();
		
		auto startToLeft = new NFAEdge(start, left.first, '\0');
		auto startToRight = new NFAEdge(start, right.first, '\0');
		auto leftToEnd = new NFAEdge(left.second, end, '\0');
		auto rightToEnd = new NFAEdge(right.second, end, '\0');
		
		return make_pair(start, end);
	}
	else
	{
		return rightNode_->ConstructNFA();
	}
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
	auto left = leftNode_->ConstructNFA();
	auto right = rightNode_->ConstructNFA();
	
	for (auto edge : right.first->outEdges_)
	{
		edge->startState_ = left.second;
		left.second->outEdges_.push_back(edge);
	}
		
	return make_pair(left.first, right.second);
}

// Class ASTConcat End

//ASTRepeat::ASTRepeat(ASTNode *node, int min, int max)
//	: node_(node), min_(min), max_(max)
//{
//}
//
//void ASTRepeat::Print()
//{
//	if (node_)
//		node_->Print();
//	cout << "重复 " << min_ << "次到 " << max_ << "次" << endl;
//}
//
//StatePtrPair ASTRepeat::ConstructNFA()
//{
//	auto repeatStart = new NFAState();
//	auto repeatEnd = new NFAState();
//	auto repeatPair = node_->ConstructNFA();
//	auto repeatInEdge = new NFAEdge(repeatStart, repeatPair.first, '\0');
//	auto repeatOutEdge = new NFAEdge(repeatPair.second, repeatEnd, '\0');
//	
//	for (int i = 0; i <= min_; ++i)
//	{
//		// newEdge = 
//	}
//
//	if (max_ == -1)
//	{
//
//	}
//}

// Class ASTRepeat End

ASTStar::ASTStar(ASTNode *node) : node_(node)
{
}

void ASTStar::Print()
{
	if (node_)
		node_->Print();
	cout << "*" << endl;
}

StatePtrPair ASTStar::ConstructNFA()
{
	auto node = node_->ConstructNFA();
	auto start = new NFAState();
	auto end = new NFAState();
	
	auto startToNode = new NFAEdge(start, node.first, '\0');
	auto startToEnd = new NFAEdge(start, end, '\0');
	auto nodeToNode = new NFAEdge(node.second, node.first, '\0');
	auto nodeToEnd = new NFAEdge(node.second, end, '\0');
	
	return make_pair(start, end);
}

// class ASTStar end

//ASTPlus::ASTPlus(ASTNode *node) : node_(node)
//{
//}
//
//void ASTPlus::Print()
//{
//	if (node_)
//		node_->Print();
//	cout << "+" << endl;
//}
//
//StatePtrPair ASTPlus::ConstructNFA()
//{
//
//}
//
//// class ASTPlus end
//
//ASTInterrogation::ASTInterrogation(ASTNode *node) : node_(node)
//{
//}
//
//void ASTInterrogation::Print()
//{
//	if (node_)
//		node_->Print();
//	cout << "?" << endl;
//}
//
//StatePtrPair ASTInterrogation::ConstructNFA()
//{
//}
// class ASTInterrogation end

ASTFactor::ASTFactor(char ch) : ch_(ch)
{
}

void ASTFactor::Print()
{
	cout << ch_ << endl;
}

StatePtrPair ASTFactor::ConstructNFA()
{
	auto start	= new NFAState();
	auto end = new NFAState();
	auto edge = new NFAEdge(start, end, ch_);
	return make_pair(start, end);
}

// Class SATFactor End