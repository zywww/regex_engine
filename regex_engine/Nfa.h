#ifndef NFA_H
#define NFA_H

#include <vector>
#include <string>
#include <set>

class NfaEdge;

class NfaState
{
public:
	std::vector<NfaEdge*>		inEdges_;
	std::vector<NfaEdge*>		outEdges_;
	bool						accept = false;
};

class NfaEdge
{
public:
	NfaEdge(NfaState *start, NfaState *end, char match);

	NfaState				*startState_;
	NfaState				*endState_;
	char					matchContent_;

	// void					initEdge(NfaState *start, NfaState *end);
};



bool					RunNfa(NfaState *start, std::string matchString);
std::set<NfaState*>		EpsilonClosure(std::set<NfaState*> oldSet);
std::set<NfaState*>		Move(std::set<NfaState*> oldSet, char ch);
void					AddState(std::set<NfaState*> &newSet, NfaState *state);

#endif
