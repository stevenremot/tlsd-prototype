#ifndef SUBSYSTEMSMANAGER_H
#define SUBSYSTEMSMANAGER_H

#include <vector>

#include "Subsystem.h"
#include "../Blackboard.h"
#include "../WorkingMemory.h"


namespace AI
{
    namespace Subsystem
    {
        /**
         * Add, remove and manage the subsystems for the AI module
         */
        class SubSystemsManager
        {
        public:
            SubSystemsManager(Blackboard & blackboard, WorkingMemory& memory)
                : blackboard_(blackboard), memory_(memory){}

            void addSubsystem(const Subsystem::SubsystemType & type);

            void upadateSubsystems();


        private:
            std::vector<Subsystem*> subSystemsList_;
            Blackboard& blackboard_;
            WorkingMemory& memory_;
        };
    }

}

#endif // SUBSYSTEMSMANAGER_H
