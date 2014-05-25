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
        //typedef float(*TransitionFunction)();

        //static float f() {return 1.0;}

        BasicStateMachine(const State& initialState) : currentState_(initialState)
        {
            addState(currentState_);
        }

        void addState(const State& state);
        /*
         * Add a transition from state1 to state2.
         * The weight of the transition must be set between 0 and 1

        void addTransition(const State& state1, const State& state2, float weight);
        void addTransition(const State& state1, const State& state2, TransitionFunction f);
        */
        void addTransition(const State& state1, const State& state2);
        //void nextStep();

        void goToState(const State& nextState);

        std::vector<State> getNextStates(const State& state) const;
        const State& getCurrentState() const {return currentState_;}
    private:


        State currentState_;
        std::vector<State> states_;
        //std::map<std::pair<State,State>, float> transitions_;
        //std::map<std::pair<State,State>, TransitionFunction> transitions_;
        std::map<std::pair<State,State>, bool> transitions_;
    };

    /**
     * TODO : correspondance Action -> Transition
     */
    class BasicAiModule : public AiModule
    {
    public:

        typedef float(*TransitionFunction)(Ecs::ComponentGroup& components, const Blackboard& blackboard);

        struct Transition
        {
            Transition();
            Transition(const Action::Action::ActionType& actionType, TransitionFunction transitionFunction)
                : actionType_(actionType), transitionFunction_(transitionFunction){}
            Action::Action::ActionType actionType_;
            TransitionFunction transitionFunction_;
        };

        BasicAiModule(Ecs::ComponentGroup& components, Blackboard& blackboard, const BasicStateMachine::State& initialState)
            : AiModule(components, blackboard), stateMachine_(initialState) {}

        /**
         * Look for the next state in the state machine and add the action related to the ttransition in the plan.
         */
        virtual void computeNewPlan();

        void addState(const BasicStateMachine::State& state);
        void addTransition(const BasicStateMachine::State& state1, const BasicStateMachine::State& state2, const Transition& transition);

        //BasicStateMachine& getStateMachine() {return stateMachine_;}

    private:
        bool hasAction(const Action::Action::ActionType& actionType);

        BasicStateMachine stateMachine_;
        std::map<std::pair<BasicStateMachine::State,BasicStateMachine::State>, Transition> transitions_;

    };

}

#endif // AI_BASICAIMODULE_H
