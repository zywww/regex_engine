#include "Nfa.h"

using std::set;
using std::string;

NfaEdge::NfaEdge(NfaState *start, NfaState *end, char match)
	: startState_(start), endState_(end), matchContent_(match)
{
	startState_->outEdges_.push_back(this);
	endState_->inEdges_.push_back(this);
}

bool RunNfa(NfaState *start, string matchString)
{
	auto stateSet = EpsilonClosure({ start });
	string::size_type index = 0;
	char ch = matchString[index];

	while (index < matchString.length())
	{
		stateSet = EpsilonClosure(Move(stateSet, ch));
		ch = matchString[++index];
	}

	bool accept = false;
	for (auto state : stateSet)
		if (state->accept == true)
			accept = true;

	return accept;
	
}

set<NfaState*> EpsilonClosure(set<NfaState*> oldSet)
{
	set<NfaState*> newSet;
	for (auto state : oldSet)
		if (newSet.find(state) == newSet.end())
			AddState(newSet, state);
	
	return newSet;
}

set<NfaState*> Move(set<NfaState*> oldSet, char ch)
{
	auto newSet = set<NfaState*>();
	for (auto state : oldSet)
		for (auto edge : state->outEdges_)
		{
			if (edge->matchContent_ == ch)
				newSet.insert(edge->endState_);
		}

	return newSet;
}

void AddState(std::set<NfaState*> &newSet, NfaState *state)
{
	newSet.insert(state);
	for (auto outEdge : state->outEdges_)
	{
		if (outEdge->matchContent_ == '\0')
			if (newSet.find(outEdge->endState_) == newSet.end())
				AddState(newSet, outEdge->endState_);
	}
}