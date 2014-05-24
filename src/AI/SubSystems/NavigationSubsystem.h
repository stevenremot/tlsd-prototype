#ifndef NAVIGATIONSUBSYSTEM_H
#define NAVIGATIONSUBSYSTEM_H

#include "Subsystem.h"
#include "../../Geometry/Vec3D.h"


namespace AI
{
    namespace Subsystem
    {
        /**
         * Vérifie si la destination actuelle est bien la même que celle du blackboard.
         * Recalcule le chemin sinon
         * Doit avoir accès au NavMesh ?
         * Envoie le chemin à l'agent ?
         */
        class NavigationSubSystem : public AI::Subsystem::Subsystem
        {
        public:
            static const Subsystem::SubsystemType Type;

            NavigationSubSystem(Blackboard& blackboard);
            ~NavigationSubSystem(){}
            /**
             * @brief updatePath
             * Vérifie si la cible actuelle est bien celle inscrite dans la blackboard
             * Si oui, ne fait rien.
             * Sinon, recalcule une chemin
             */
            void updatePath();
            void findPathToGoal();
            virtual bool update();
            virtual void executeAction(Action::Action *action);

        private:
            Geometry::Vec3Df navigationTarget_;
            //Geometry::Vec3Df currentPosition_;
            bool isFinished_;
        };
    }
}

#endif // NAVIGATIONSUBSYSTEM_H
