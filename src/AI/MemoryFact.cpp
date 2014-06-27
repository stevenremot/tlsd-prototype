#include "MemoryFact.h"

namespace AI
{
    MemoryFact::MemoryFact()
    {

    }

    MemoryFact::MemoryFact(MemoryFactType factType, float factBelief) : factType_(factType), factBelief_(factBelief)
    {
    }

    bool MemoryFact::operator ==(const MemoryFact & otherFact) const
    {
        return (factType_ == otherFact.getFactType())
                && (factBelief_ == otherFact.getFactBelief())
                && (characterId_ == otherFact.getCharacterId())
                && (position_ == otherFact.getPosition());
    }

}

