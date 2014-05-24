#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "../Ecs/Component.h"
#include "WorkingMemory.h"
#include "Blackboard.h"
#include "Sensor/SensorManager.h"
#include "SubSystems/SubsystemsManager.h"
#include "AiModule.h"


namespace AI
{
     /**
     * Component for all the NPC controlled by the computer
     */
    class AiComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        AiComponent(Ecs::World& world)
            : Component(Type), memory_(), blackboard_(),
              subsystemsManager_(blackboard_,memory_),
              sensorsManager_(world, memory_), aiModule_(NULL) {}

        void setAiModule(AiModule* aiModule) {aiModule_ = aiModule;}
        AiModule* getAiModule() {return aiModule_;}

        Blackboard& getBlackboard() {return blackboard_;}

        Subsystem::SubSystemsManager& getSubsystemsManager()
        {
            return subsystemsManager_;
        }
        Sensor::SensorsManager& getSensorsManager()
        {
            return sensorsManager_;
        }

    private:
        WorkingMemory memory_;
        Blackboard blackboard_;
        Subsystem::SubSystemsManager subsystemsManager_;
        Sensor::SensorsManager sensorsManager_;
        AiModule* aiModule_;
    };
}
#endif // AICOMPONENT_H
