#ifndef WORKINGMEMORY_H
#define WORKINGMEMORY_H

#include <vector>
#include <map>

#include "MemoryFact.h"

using std::vector;
using std::map;

using AI::MemoryFact;

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
        typedef vector<MemoryFact*> MemoryFactsList;
        typedef map<MemoryFact::MemoryFactType, MemoryFactsList> MemoryFactsMap;

        WorkingMemory();
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
#endif // WORKINGMEMORY_H
