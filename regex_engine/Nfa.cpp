#include "NFA.h"

using std::set;
using std::string;

NFAEdge::NFAEdge(NFAState *start, NFAState *end, char match)
	: startState_(start), endState_(end), matchContent_(match)
{
	startState_->outEdges_.push_back(this);
	endState_->inEdges_.push_back(this);
}

bool RunNFA(NFAState *start, string matchString)
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

set<NFAState*> EpsilonClosure(set<NFAState*> oldSet)
{
	set<NFAState*> newSet;
	for (auto state : oldSet)
		if (newSet.find(state) == newSet.end())
			AddState(newSet, state);
	
	return newSet;
}

set<NFAState*> Move(set<NFAState*> oldSet, char ch)
{
	auto newSet = set<NFAState*>();
	for (auto state : oldSet)
		for (auto edge : state->outEdges_)
		{
			if (edge->matchContent_ == ch)
				newSet.insert(edge->endState_);
		}

	return newSet;
}

void AddState(std::set<NFAState*> &newSet, NFAState *state)
{
	newSet.insert(state);
	for (auto outEdge : state->outEdges_)
	{
		if (outEdge->matchContent_ == '\0')
			if (newSet.find(outEdge->endState_) == newSet.end())
				AddState(newSet, outEdge->endState_);
	}
}