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

#ifndef AI_BASICAIMODULE_H
#define AI_BASICAIMODULE_H

#include "AiModule.h"

#include <string>
#include <vector>
#include <map>

namespace AI
{
    class BasicStateMachine
    {
    public:
        typedef std::string State;

        BasicStateMachine(const State& initialState) : currentState_(initialState)
        {
            addState(currentState_);
        }

        void addState(const State& state);

        void addTransition(const State& state1, const State& state2);
        //void nextStep();

        void goToState(const State& nextState);

        std::vector<State> getNextStates(const State& state) const;
        const State& getCurrentState() const {return currentState_;}

    private:
        State currentState_;
        State nextState_;
        std::vector<State> states_;
        std::map<std::pair<State,State>, bool> transitions_;
    };

    /**
     * TODO : correspondance Action -> Transition
     */
    class BasicAiModule : public AiModule
    {
    public:

        typedef float(*TransitionFunction)(Ecs::ComponentGroup& components);

        struct Transition
        {
            Transition();
            Transition(const Action::Action::ActionType& actionType, TransitionFunction transitionFunction)
                : actionType_(actionType), transitionFunction_(transitionFunction){}
            Action::Action::ActionType actionType_;
            TransitionFunction transitionFunction_;
        };

        BasicAiModule(const BasicStateMachine::State& initialState)
            : AiModule(), stateMachine_(initialState) {}

        /**
         * Look for the next state in the state machine and add the action related to the ttransition in the plan.
         */
        virtual void computeNewPlan(Ecs::ComponentGroup& components);

        void addState(const BasicStateMachine::State& state);
        void addTransition(const BasicStateMachine::State& state1, const BasicStateMachine::State& state2, const Transition& transition);


    private:
        bool hasAction(const Action::Action::ActionType& actionType);

        BasicStateMachine stateMachine_;
        std::map<std::pair<BasicStateMachine::State,BasicStateMachine::State>, Transition> transitions_;

    };

}

#endif // AI_BASICAIMODULE_H
