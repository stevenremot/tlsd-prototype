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

#include "MemoryComponent.h"

namespace AI
{
    const Ecs::Component::Type MemoryComponent::Type = "memory";

    const std::vector<Ecs::Component::Type> MemoryComponent::Dependencies;


    MemoryComponent::~MemoryComponent()
    {
        cleanMemory();
    }

    void MemoryComponent::cleanMemory()
    {
        memoryFactsMap_.clear();
        while (!memoryFacts_.empty())
        {
            MemoryFact* fact = memoryFacts_.back();
            if (fact != NULL)
                delete fact;
            memoryFacts_.pop_back();
        }
    }

    void MemoryComponent::addMemoryFact(MemoryFact *fact)
    {
        // Add the fact to the map
        MemoryFactsList& facts = memoryFactsMap_[fact->getFactType()];
        facts.push_back(fact);
        // Add it to the global list of facts
        memoryFacts_.push_back(fact);
    }

    void MemoryComponent::removeMemoryFact(MemoryFact * fact)
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

    bool MemoryComponent::getMemoryFactsByType(const MemoryFact::MemoryFactType& memoryFactType, MemoryFactsList& factsList)
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
