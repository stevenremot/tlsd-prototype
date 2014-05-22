#include "WorkingMemory.h"

namespace AI
{

    WorkingMemory::WorkingMemory()
    {
        memoryFacts_.clear();
    }

    WorkingMemory::~WorkingMemory()
    {
    }

    void WorkingMemory::addMemoryFact(MemoryFact *fact)
    {
        // Add the fact to the map
        MemoryFactsList& facts = memoryFactsMap_[fact->getFactType()];
        facts.push_back(fact);
        // Add it to the global list of facts
        memoryFacts_.push_back(fact);
    }

    void WorkingMemory::removeMemoryFact(MemoryFact * fact)
    {
        // Try to find the fact in list. If it exists, remove it from the list.
        for(MemoryFactsList::iterator it = memoryFacts_.begin(); it != memoryFacts_.end(); ++it)
        {
            if (*(*it) == *fact)
            {
                memoryFacts_.erase(it);
                if (it == memoryFacts_.end())
                    return;
            }
        }
        // Find and remove the fact from the map
        MemoryFactsMap::const_iterator it;
        it = memoryFactsMap_.find(fact->getFactType());
        if(it != memoryFactsMap_.end())
        {
            MemoryFactsList& factsList = memoryFactsMap_[fact->getFactType()];
            for(MemoryFactsList::iterator it2 = factsList.begin(); it2 != factsList.end(); ++it2)
            {
                if (*(*it2) == *fact)
                {
                    factsList.erase(it2);
                    if (it2 == factsList.end())
                        return;
                }
            }
        }

    }

    bool WorkingMemory::getMemoryFactsByType(const MemoryFact::MemoryFactType& memoryFactType, MemoryFactsList& factsList)
    {
        factsList.clear();
        MemoryFactsMap::iterator it = memoryFactsMap_.find(memoryFactType);
        if(it != memoryFactsMap_.end())
        {
            factsList = it->second;
            return true;
        }
        else
            return false;
    }
}
