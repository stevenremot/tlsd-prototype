#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "../Geometry/Vec3D.h"
#include "../Ecs/Component.h"
#include "../Geometry/PositionComponent.h"

namespace Physics
{
  /**
   * Component for moving entities
   */
  class MovementComponent : public Ecs::Component
  {
  public:
      static const Ecs::Component::Type Type;

      MovementComponent(const Geometry::Vec3Df& velocity):
          Component(Type),
          velocity_(velocity)
      {}

      virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
      {
          if (Dependencies.empty())
          {
              Dependencies.push_back(Geometry::PositionComponent::Type);
          }
          return Dependencies;
      }

      const Geometry::Vec3Df& getVelocity() const
      {
          return velocity_;
      }

      void setVelocity(const Geometry::Vec3Df& velocity)
      {
          velocity_ = velocity;
      }

  private:
      static std::vector<Ecs::Component::Type> Dependencies;

      Geometry::Vec3Df velocity_;
  };
}
#endif // MOVEMENTCOMPONENT_H
