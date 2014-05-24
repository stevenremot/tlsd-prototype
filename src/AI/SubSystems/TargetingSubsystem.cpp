#include "TargetingSubsystem.h"

#include <cfloat>
#include <vector>

#include "../../Geometry/Vec3D.h"

using std::vector;

using Geometry::Vec3Df;

namespace AI
{
    namespace Subsystem
    {

        const Subsystem::SubsystemType TargetingSubsystem::Type = "TargetingSubsystem";

        TargetingSubsystem::TargetingSubsystem(Blackboard&blackboard, WorkingMemory&memory)
            : Subsystem(Type, blackboard), memory_(memory), targetId_(-1)
        {
        }

        TargetingSubsystem::~TargetingSubsystem()
        {}

        bool TargetingSubsystem::update()
        {
            MemoryFact::MemoryFactType factType = "sightFact";
            vector<MemoryFact*> ennemyFacts;
            memory_.getMemoryFactsByType(factType, ennemyFacts);
            if (ennemyFacts.size() == 0)
            {
                targetId_ = - 1;
            }
            else
            {
                float currentFactBelief = 0.0;
                float currentDistance = FLT_MAX;
                for(unsigned int i = 0; i < ennemyFacts.size(); i++)
                {
                    MemoryFact * ennemyFact = ennemyFacts[i];
                    float factBelief = ennemyFact->getFactBelief();
                    const Vec3Df& position = ennemyFact->getPosition();
                    float distance = position.getLength();
                    if (currentFactBelief/(FLT_EPSILON + currentDistance) < factBelief/(FLT_EPSILON + distance))
                    {
                        targetId_ = ennemyFact->getCharacterId();
                        currentFactBelief = factBelief;
                        currentDistance = distance;
                        blackboard_.setNavigationTarget(position);
                    }
                }
            }
            blackboard_.setTargetId(targetId_);
            return true;
        }
    }
}
