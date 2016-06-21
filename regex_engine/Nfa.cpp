#include "Nfa.h"


NfaEdge::NfaEdge(NfaState *start, NfaState *end, char match)
	: startState_(start), endState_(end), matchContent_(match)
{
	startState_->outEdges_.push_back(this);
	endState_->inEdges_.push_back(this);
}

bool RunNfa(NfaState *start, std::string matchString)
{
	auto stateSet = EpsilonClosure({ start });
	std::string::size_type index = 0;
	char ch = matchString[index];

	while (index <= matchString.length())
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

std::set<NfaState*> EpsilonClosure(std::set<NfaState*> oldSet)
{

}

std::set<NfaState*> Move(std::set<NfaState*> oldSet, char ch)
{

}