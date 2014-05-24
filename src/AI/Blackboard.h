#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../Geometry/Vec3D.h"
#include "../Ecs/Entity.h"

/**
 * Gather getters & setters for the communication between subsystems.
 *
 */
namespace AI
{
    class Blackboard
    {
    public:
        Blackboard() : targetId_(-1) {}
        ~Blackboard(){}
        /**
         * Write a new navigation's target on the blackboard
         */
        void setNavigationTarget(const Geometry::Vec3Df& navigationTarget) {navigationTarget_ = navigationTarget;}

        const Geometry::Vec3Df& getNavigationTarget() const {return navigationTarget_;}

        void setCurrentPosition(const Geometry::Vec3Df& currentPosition) {currentPosition_ = currentPosition;}

        const Geometry::Vec3Df& getCurrentPosition() const {return currentPosition_;}
        /**
         * @brief setNavigationStatus
         * Utilise par le navigation manager pour indiquer s'il a fini son trajet
         * @param _currentPosition
         */
        void setNavigationStatus(bool isFinished);
        /**
         * @brief getNavigationStatus
         * Utilisé par ?
         * @return
         */
        bool getNavigationStatus() const;
        /**
         * Write a new target's id on the blackboard
         */
        void setTargetId(Ecs::Entity targetId) {targetId_ = targetId;}
        /**
         * Get the target's id currently written on the blackboard
         */
        Ecs::Entity getTargetId() const {return targetId_;}
    private:
        /**
         * Id of the target selected by the targeting subsystem.
         */
        Ecs::Entity targetId_;
        /**
         * Current targeted position.
         */
        Geometry::Vec3Df navigationTarget_;
        /**
         * Current position of the entity
         */
        Geometry::Vec3Df currentPosition_;

    };
}

#endif // BLACKBOARD_H
