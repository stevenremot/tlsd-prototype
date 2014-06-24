#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <string>

#include "../Blackboard.h"
#include "../MemoryFact.h"

#include "../Action/Action.h"

/**
 * Base class for the subsystems of the AI module.
 * Warning : this class has nothing to do with Ecs::System!
 */
namespace AI
{
    namespace Subsystem
    {
        class Subsystem
        {
        public:
            typedef std::string SubsystemType;

            Subsystem(const SubsystemType & subsystemType, Blackboard& blackboard)
                : subsystemType_(subsystemType), blackboard_(blackboard) {}
            virtual ~Subsystem(){}
            virtual bool update() = 0;
            virtual void executeAction(Action::Action* action) = 0;

            const SubsystemType & getSubsystemType() const
            {
                return subsystemType_;
            }

        protected:
            SubsystemType subsystemType_;
            AI::Blackboard& blackboard_;
        };
    }
}



#endif // SUBSYSTEM_H
