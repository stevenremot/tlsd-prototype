/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef AI_MEMORYFACT_H
#define AI_MEMORYFACT_H

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
    const Geometry::Vec3Df& getPosition() const {return position_;}

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
#endif // AI_MEMORYFACT_H
