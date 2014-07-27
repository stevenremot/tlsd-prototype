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

#ifndef CHARACTER_STATISTICS_COMPONENT_H
#define CHARACTER_STATISTICS_COMPONENT_H

#include "../Core/Time.h"
#include "../Ecs/Component.h"
#include "Statistics.h"

namespace Character
{
    /**
     * Component for entities that have statistics.
     */
    class StatisticsComponent: public Ecs::Component
    {
    public:
        static const Type Type;

        StatisticsComponent(const Statistics& statistics):
            Component(Type),
            statistics_(statistics),
            lastTimeHurt_()
        {}

        virtual Component* clone() const
        {
            return new StatisticsComponent(statistics_);
        }

        virtual const std::vector<Component::Type>& getDependentComponents()
        {
            return dependentComponents_;
        }

        Statistics& getStatistics() { return statistics_; }
        const Statistics& getStatistics() const { return statistics_; }

        const Core::TimePoint& getLastTimeHurt()
        {
            return lastTimeHurt_;
        }

        void setLastTimeHurt(const Core::TimePoint& lastTimeHurt)
        {
            lastTimeHurt_ = lastTimeHurt;
        }

    private:
        static const std::vector<Component::Type> dependentComponents_;
        Statistics statistics_;
        Core::TimePoint lastTimeHurt_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
