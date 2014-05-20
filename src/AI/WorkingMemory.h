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
 * @brief WorkingMemory
 * Le planner y cherche les memory facts les plus intéressants pour prendre une décision ou exécuter une action.
 */
/**
 * Working memory is where all the memory's facts created by the sensors are stored.
 *
 *  Warning : WorkingMemory is not responsible for cleaning the memory's facts.
 */
class WorkingMemory
{
public:

    typedef vector<MemoryFact*> MemoryFactsList;

    WorkingMemory();
    ~WorkingMemory();
    void addMemoryFact(MemoryFact* fact);
    void removeMemoryFact(MemoryFact* fact);

    MemoryFactsList getMemoryFacts() const {return memoryFacts_;}
    const MemoryFactsList& getMemoryFactsByType(const MemoryFact::MemoryFactType & memoryFactType);
    // Pour l'instant, un getter par type de fact, mais il faudrait une méthode plus generique
    MemoryFact* getEnnemyFactFromCharacterId(int id);
private:
    typedef map<MemoryFact::MemoryFactType, MemoryFactsList> MemoryFactsMap;

    MemoryFactsList memoryFacts_;
    MemoryFactsMap memoryFactsMap_;
    
};
}
#endif // WORKINGMEMORY_H
