#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "../Geometry/Vec3D.h"
#include "../Ecs/Component.h"
#include "../Geometry/PositionComponent.h"

namespace Physics
{
  using Geometry::Vec3Df;

  /**
   * Component for moving entities
   */
  class MovementComponent : public Ecs::Component
  {
  public:
      static const Ecs::Component::Type Type;

      MovementComponent(const Vec3Df& velocity):
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

      const Vec3Df& getVelocity() const
      {
          return velocity_;
      }

      void setVelocity(const Vec3Df& velocity)
      {
          velocity_ = velocity;
      }

  private:
      Vec3Df velocity_;

      static std::vector<Ecs::Component::Type> Dependencies;
  };
}
#endif // MOVEMENTCOMPONENT_H
