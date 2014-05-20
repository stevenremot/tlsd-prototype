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

  /*
  WorkingMemory::~WorkingMemory()
  {
    MemoryFactsList::iterator it = memoryFacts_.begin();
    while(it != memoryFacts_.end())
      {
        MemoryFact * fact = *it;
        delete fact;
        // erase renvoie un iterateur vers le prochain iterateur valide, pas besoin d'incrementer.
        memoryFacts_.erase(it);
      }
    memoryFacts_.clear();
  }
  */

  void WorkingMemory::addMemoryFact(MemoryFact *fact)
  {
    MemoryFactsMap::iterator it;
    it = memoryFactsMap_.find(fact->getFactType());
    // If the fact's type is not registered in the map, add it.
    if(it == memoryFactsMap_.end())
      {
	memoryFactsMap_[fact->getFactType()].push_back(fact);
      }
    else // add the fact to the list of the facts of the same type.
      {
	MemoryFactsList& facts = memoryFactsMap_[fact->getFactType()];
	facts.push_back(fact);
      }
    memoryFacts_.push_back(fact);
  }

  void WorkingMemory::removeMemoryFact(MemoryFact * fact)
  {
    // Try to find the fact in list. If it exists, remove it from the list. 
    for(MemoryFactsList::iterator it = memoryFacts_.begin(); it != memoryFacts_.end(); ++it)
      {
	if ((*it) == fact)
	  {
	    //MemoryFact * fact = *it;
	    //delete fact;
	    memoryFacts_.erase(it);
	    if (it == memoryFacts_.end())
	      return;
	  }
      }
    // TO DO : remove the fact from the map
  }
}
