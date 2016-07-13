#ifndef NFA_H
#define NFA_H

#include <vector>
#include <string>
#include <set>

class NFAEdge;

class NFAState
{
public:
	std::vector<NFAEdge*>		inEdges_;
	std::vector<NFAEdge*>		outEdges_;
	bool						accept = false;
};

class NFAEdge
{
public:
	NFAEdge(NFAState *start, NFAState *end, char match);

	NFAState				*startState_;
	NFAState				*endState_;
	char					matchContent_;

	// void					initEdge(NfaState *start, NfaState *end);
};



bool					RunNFA(NFAState *start, std::string matchString);
std::set<NFAState*>		EpsilonClosure(std::set<NFAState*> oldSet);
std::set<NFAState*>		Move(std::set<NFAState*> oldSet, char ch);
void					AddState(std::set<NFAState*> &newSet, NFAState *state);

#endif
