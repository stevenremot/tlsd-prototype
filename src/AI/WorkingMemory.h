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

#ifndef AI_WORKINGMEMORY_H
#define AI_WORKINGMEMORY_H

#include <vector>
#include <map>

#include "MemoryFact.h"

namespace AI
{

/**
 * Working memory is where all the memory's facts created by the sensors are stored.
 *
 *  Warning : WorkingMemory is not responsible for cleaning the memory's facts.
 */
    class WorkingMemory
    {
    public:
        typedef std::vector<MemoryFact*> MemoryFactsList;
        typedef std::map<MemoryFact::MemoryFactType, MemoryFactsList> MemoryFactsMap;

        WorkingMemory();
        /**
          * Clean all the remaining memory facts
          */
        ~WorkingMemory();
        void addMemoryFact(MemoryFact* fact);
        void removeMemoryFact(MemoryFact* fact);

        MemoryFactsList getMemoryFacts() const {return memoryFacts_;}

        /**
         * Get the list of the memory's facts of the specified type.
         * @return true if the fact's type is registered in the map, false otherwise.
         */
        bool getMemoryFactsByType(const MemoryFact::MemoryFactType & memoryFactType, MemoryFactsList& factsList);

        MemoryFactsMap getMemoryFactsMap() const {return memoryFactsMap_;}
        WorkingMemory &operator = (const WorkingMemory &w)
        {
            memoryFacts_ = w.getMemoryFacts();
            memoryFactsMap_ = w.getMemoryFactsMap();
            return *this;
        }

    private:
        MemoryFactsList memoryFacts_;
        MemoryFactsMap memoryFactsMap_;

    };
}
#endif // AI_WORKINGMEMORY_H
