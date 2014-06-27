#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "../Ecs/Component.h"
#include "WorkingMemory.h"
#include "Blackboard.h"
#include "Sensor/SensorManager.h"
#include "SubSystems/SubsystemsManager.h"
#include "AiModule.h"

#include "../Geometry/PositionComponent.h"
#include "../Physics/MovementComponent.h"


namespace AI
{
     /**
     * Component for all the NPC controlled by the computer
     */
    class AiComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        // TODO use a concurrent ressource here
        AiComponent(Ecs::Entity entity, Ecs::World& world)
            : Component(Type),
              entity_(entity), memory_(), blackboard_(),
              subsystemsManager_(entity, world, blackboard_,memory_),
              sensorsManager_(entity, world, memory_), aiModule_(NULL) {}

        AiComponent(const AiComponent& aiComp):
            Component(Type),
            entity_(aiComp.entity_),
            memory_(aiComp.memory_),
            blackboard_(aiComp.blackboard_),
            subsystemsManager_(aiComp.subsystemsManager_),
            sensorsManager_(aiComp.sensorsManager_),
            aiModule_(aiComp.aiModule_)
        {}

        ~AiComponent();

        virtual Component* clone() const
        {
            return new AiComponent(*this);
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            if(Dependencies.empty())
            {
                Dependencies.push_back(Geometry::PositionComponent::Type);
                Dependencies.push_back(Physics::MovementComponent::Type);
            }
            return Dependencies;
        }

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
	static std::vector<Ecs::Component::Type> Dependencies;

        const Ecs::Entity entity_;
        WorkingMemory memory_;
        Blackboard blackboard_;
        Subsystem::SubSystemsManager subsystemsManager_;
        Sensor::SensorsManager sensorsManager_;
        AiModule* aiModule_;

    };
}
#endif // AICOMPONENT_H
