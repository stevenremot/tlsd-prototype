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

#ifndef WORLD_CHUNK_H
#define WORLD_CHUNK_H

#include <vector>

#include "../Ecs/SharedEntity.h"
#include "GroundCoefficients.h"

namespace World
{
    /**
     * Class for a chunk
     *
     * A chunk is a square part of the world containing its entities
     * It has a state describing its loading status
     */
    class Chunk
    {
    public:
        typedef std::vector<Ecs::SharedEntity> EntityCollection;
        enum State { NotLoadedState, PreparedState, GeneratedState };

        const EntityCollection& getBaseEntities() const { return baseEntities_; }
        const EntityCollection& getFinalEntities() const { return finalEntities_; }
        const GroundCoefficients& getCoefficients() const { return coefficients_; }

        void setBaseEntities(const EntityCollection& baseEntities)
        {
            baseEntities_ = baseEntities;
        }

        void setFinalEntities(const EntityCollection& finalEntities)
        {
            finalEntities_ = finalEntities;
        }
        void setCoefficients(const GroundCoefficients& coefficients)
        {
            coefficients_ = coefficients;
        }

        State getState() const
        {
            return state_;
        }

        void setState(State state)
        {
            state_ = state;
        }

    private:
        EntityCollection baseEntities_;
        EntityCollection finalEntities_;
        GroundCoefficients coefficients_;
        State state_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
