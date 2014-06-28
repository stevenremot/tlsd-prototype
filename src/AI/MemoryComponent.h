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

#ifndef AI_MEMORYCOMPONENT_H
#define AI_MEMORYCOMPONENT_H

#include "MemoryFact.h"
#include "../Ecs/Component.h"

#include <map>

namespace AI
{
    class MemoryComponent : public Ecs::Component
    {
    public:

        static const Ecs::Component::Type Type;

        static const std::vector<Ecs::Component::Type> Dependencies;

        typedef std::vector<MemoryFact*> MemoryFactsList;
        typedef std::map<MemoryFact::MemoryFactType, MemoryFactsList> MemoryFactsMap;

        MemoryComponent() :
            Component(Type),
            memoryFacts_(),
            memoryFactsMap_()
        {}

        /**
          * Clean all the remaining memory facts
          */
        ~MemoryComponent();

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            return Dependencies;
        }

        virtual Component* clone() const
        {
            return new MemoryComponent(*this);
        }

        void cleanMemory();

        void addMemoryFact(MemoryFact* fact);
        void removeMemoryFact(MemoryFact* fact);

        MemoryFactsList getMemoryFacts() const {return memoryFacts_;}

        /**
         * Get the list of the memory's facts of the specified type.
         * @return true if the fact's type is registered in the map, false otherwise.
         */
        bool getMemoryFactsByType(const MemoryFact::MemoryFactType & memoryFactType, MemoryFactsList& factsList);

        MemoryFactsMap getMemoryFactsMap() const {return memoryFactsMap_;}

    private:
        MemoryFactsList memoryFacts_;
        MemoryFactsMap memoryFactsMap_;

        MemoryComponent(const MemoryComponent& mem):
            Component(Type),
            memoryFacts_(mem.memoryFacts_),
            memoryFactsMap_(mem.memoryFactsMap_)
        {}
    };
}
#endif // AI_MEMORYCOMPONENT_H
