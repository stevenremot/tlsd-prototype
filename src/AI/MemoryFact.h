#ifndef MEMORYFACT_H
#define MEMORYFACT_H

#include <string>

#include "../Geometry/Vec3D.h"
#include "../Ecs/Entity.h"

namespace AI
{
/**
 * Class for the facts in the memory of the entity.
 * 
 * Some attributes might be unset, check the fact's type first to know relevant attributes.
 *
 */
class MemoryFact
{
public:

    typedef std::string MemoryFactType;

    MemoryFact();
    MemoryFact(MemoryFactType factType, float factBelief);

    MemoryFactType getFactType() const {return factType_;}
    float getFactBelief() const {return factBelief_;}
    void setFactBelief(float factBelief) {factBelief_ = factBelief;}

    // Getters & setters for attributes
    void setCharacterId(Ecs::Entity characterId) {characterId_ = characterId;}
    void setPosition(const Geometry::Vec3Df& position) { position_ = position;}

    Ecs::Entity getCharacterId() const {return characterId_;}
    Geometry::Vec3Df getPosition() const {return position_;}

    bool operator ==(const MemoryFact & otherFact) const;

private:
    MemoryFactType factType_;
    float factBelief_;

    //Attributes
    Geometry::Vec3Df  position_;
    Ecs::Entity characterId_;
    // To be continued...

};

}
#endif // MEMORYFACT_H
