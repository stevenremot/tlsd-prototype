#ifndef PLAN_H
#define PLAN_H

namespace AI
{
    namespace Plan
    {
        /**
         * The base class Plan is the super class of NavigationPlan and AiPLan.
         *
         */
        class Plan
        {
        public:
            Plan() : planCompleted_(false) {}

            bool isPlanCompleted() const {return planCompleted_;}

            virtual void goToNextStep() = 0;

        protected:
            void setPlanCompleted(bool planCompleted) {planCompleted_ = planCompleted;}
        private:
            bool planCompleted_;
        };
    }
}

#endif // PLAN_H
