#ifndef TARGETINGSUBSYSTEM_H
#define TARGETINGSUBSYSTEM_H

#include "Subsystem.h"
#include "../WorkingMemory.h"
#include "../../Ecs/Entity.h"

namespace AI
{
    namespace Subsystem
    {
        /**
         * This subsystem retrieves memory facts from working memory to set the current target of the entity.
         *
         * The choosen target is based on the memory fact with the highest belief degree.
         */
        class TargetingSubsystem : public Subsystem
        {
        public:

            static const Subsystem::SubsystemType Type;

            TargetingSubsystem(Blackboard& blackboard, WorkingMemory& memory);
            ~TargetingSubsystem();

            virtual void executeAction(Action::Action*){}

            virtual bool update();

        private:
            WorkingMemory& memory_;

            Ecs::Entity targetId_;
        };
    }
}
#endif // TARGETINGSUBSYSTEM_H
