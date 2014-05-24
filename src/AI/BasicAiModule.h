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
        typedef float(*TransitionFunction)();

        static float f() {return 1.0;}

        BasicStateMachine(const State& initialState) : currentState_(initialState)
        {
            addState(currentState_);
        }

        void addState(const State& state);
        /**
         * Add a transition from state1 to state2.
         * The weight of the transition must be set between 0 and 1
         */
        //void addTransition(const State& state1, const State& state2, float weight);
        void addTransition(const State& state1, const State& state2, TransitionFunction f);
        void nextStep();

    private:
        std::vector<State> getNextStates(const State& state) const;

        State currentState_;
        std::vector<State> states_;
        //std::map<std::pair<State,State>, float> transitions_;
        std::map<std::pair<State,State>, TransitionFunction> transitions_;
    };

    /**
     * TODO : correspondance Action -> Transition
     */
    class BasicAiModule : public AiModule
    {
    public:

        BasicAiModule(Blackboard& blackboard, const BasicStateMachine::State& initialState)
            : AiModule(blackboard), stateMachine_(initialState) {}

        virtual void computeNewPlan();

        BasicStateMachine& getStateMachine() {return stateMachine_;}

    private:
        bool hasAction(const Action::Action::ActionType& actionType);

        BasicStateMachine stateMachine_;

    };

}

#endif // AI_BASICAIMODULE_H
