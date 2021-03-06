/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include "BasicAiModule.h"

#include "Action/ActionFactory.h"

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
    void BasicStateMachine::addTransition(const State& state1, const State& state2)
    {
        transitions_.insert(std::pair< std::pair<State,State>, bool>(make_pair(state1,state2), true));
    }

    /*
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
    */

    vector<BasicStateMachine::State> BasicStateMachine::getNextStates(const State& state) const
    {
        vector<State> nextStates;
        vector<State>::const_iterator statesIt;
        for(statesIt = states_.begin(); statesIt != states_.end(); ++statesIt)
            if(transitions_.find(make_pair(state,(*statesIt))) != transitions_.end())
                nextStates.push_back((*statesIt));
        return nextStates;
    }

    void BasicStateMachine::goToState(const State& nextState)
    {
         if (transitions_.find(make_pair(currentState_, nextState)) != transitions_.end())
             currentState_ = nextState;
    }

    // Ai module's implementation

    void BasicAiModule::computeNewPlan(Ecs::ComponentGroup& components)
    {
        if(getPlan() != NULL && !getPlan()->isPlanCompleted())
            return;
        cleanPlan();
        vector<Action::Action*> newPlan;

        // Get all the possible next states
        const BasicStateMachine::State& currentState = stateMachine_.getCurrentState();
        vector<BasicStateMachine::State> nextStates = stateMachine_.getNextStates(currentState);

        float maxWeight = 0.f;
        Action::Action::ActionType actionType;
        BasicStateMachine::State nextState;

        vector<BasicStateMachine::State>::const_iterator it;
        for(it = nextStates.begin(); it != nextStates.end(); ++it)
        {
            const Transition& transition = transitions_.at(std::make_pair(currentState, (*it)));
            float weight = (*transition.transitionFunction_)(components);
            if(weight > maxWeight)
            {
                maxWeight = weight;
                nextState = (*it);
                actionType = transition.actionType_;
            }
        }
        try
        {
            /**
              * Add the action to the plan if an exception is raised ?
              */
            newPlan.push_back(Action::ActionFactory::createAction(actionType, components));
            stateMachine_.goToState(nextState);
            setPlan(new Plan::AiPlan(newPlan));
        }
        catch (const Action::CannotCreateActionException e)
        {
            return;
        }

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

    void BasicAiModule::addState(const BasicStateMachine::State &state)
    {
        stateMachine_.addState(state);
    }

    void BasicAiModule::addTransition(const BasicStateMachine::State &state1, const BasicStateMachine::State &state2, const Transition& transition)
    {
        stateMachine_.addTransition(state1, state2);
        transitions_.insert(std::pair< std::pair<BasicStateMachine::State,BasicStateMachine::State>, Transition>(make_pair(state1,state2), transition));

    }
}
