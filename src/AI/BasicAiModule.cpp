#include "BasicAiModule.h"

using std::vector;
using std::map;
using std::pair;

namespace AI
{
    // States machine's implementation
    void BasicStateMachine::addState(const State& state)
    {
        vector<State>::const_iterator it;
        for(it = states_.begin(); it != states_.end(); ++it)
            if((*it) == state)
                return;
        states_.push_back(state);
    }

//    void BasicStateMachine::addTransition(const State& state1, const State& state2, float weight)
//    {
//        transitions_.insert(std::pair< std::pair<State,State>, float>(make_pair(state1,state2), weight));
//    }

    void BasicStateMachine::addTransition(const State& state1, const State& state2, TransitionFunction f)
    {
        transitions_.insert(std::pair< std::pair<State,State>, TransitionFunction>(make_pair(state1,state2), f));
    }

    void BasicStateMachine::nextStep()
    {
        const vector<State>& nextStates = getNextStates(currentState_);
        State nextStep = currentState_;
        float maxWeight = 0.f;
        vector<State>::const_iterator it;
        for(it = nextStates.begin(); it != nextStates.end(); ++it)
        {
            TransitionFunction f = transitions_.at(make_pair(currentState_, (*it)));
            float weight = (*f)();
            //float weight = transitions_.at(make_pair(currentState_, (*it)));
            if(maxWeight < weight)
            {
                maxWeight = weight;
                nextStep = (*it);
            }
        }
        currentState_ = nextStep;
    }

    vector<BasicStateMachine::State> BasicStateMachine::getNextStates(const State& state) const
    {
        vector<State> nextStates;
        vector<State>::const_iterator statesIt;
        for(statesIt = states_.begin(); statesIt != states_.end(); ++statesIt)
            if(transitions_.find(make_pair(state,(*statesIt))) != transitions_.end())
                nextStates.push_back((*statesIt));
        return nextStates;
    }

    // Ai module's implementation

    void BasicAiModule::computeNewPlan()
    {
        stateMachine_.nextStep();
    }

    bool BasicAiModule::hasAction(const Action::Action::ActionType& actionType)
    {
        const vector<Action::Action::ActionType>& actions =  getAvailableActions();
        vector<Action::Action::ActionType>::const_iterator it;
        for(it = actions.begin(); it != actions.end(); ++it)
            if((*it) == actionType)
                return true;
        return false;
    }
}
