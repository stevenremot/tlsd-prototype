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

#ifndef AI_PLAN_PLAN_H
#define AI_PLAN_PLAN_H

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
            virtual ~Plan(){}

            bool isPlanCompleted() const {return planCompleted_;}

            virtual void goToNextStep() = 0;

        protected:
            void setPlanCompleted(bool planCompleted) {planCompleted_ = planCompleted;}
        private:
            bool planCompleted_;
        };
    }
}

#endif // AI_PLAN_PLAN_H
