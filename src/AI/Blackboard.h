#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "../Geometry/Vec3D.h"

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
         * @brief setNavigationTarget
         * Utilisé par AI module pour indiquer la nouvelle cible
         * @param _targetPosition
         */
        void setNavigationTarget(const Geometry::Vec3Df& navigationTarget) {navigationTarget_ = navigationTarget;}
        /**
         * @brief getNavigationTarget
         * Utilisé par nav manager pour savoir si ça correspond bien à son état actuel
         * @return
         */
        const Geometry::Vec3Df& getNavigationTarget() const {return navigationTarget_;}
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
         * @brief setTargetId
         * Indique l'id du personnage cible par l'agent
         * Utilise par le targeting system
         * @param targetId
         */
        void setTargetId(int targetId) {targetId_ = targetId;}
        /**
         * @brief getTargetId
         * Retourne l'id du personnage cible par l'agent
         * Utilise par le planner
         * @return
         */
        int getTargetId() const {return targetId_;}
    private:
        int targetId_;
        Geometry::Vec3Df navigationTarget_;

    };
}

#endif // BLACKBOARD_H
