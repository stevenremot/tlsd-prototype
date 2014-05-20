#ifndef MEMORYFACT_H
#define MEMORYFACT_H

#include <vector>
#include <string>

#include "../Geometry/Vec3D.h"

using std::vector;

using Geometry::Vec3Df;

namespace AI
{
/**
 * @brief The MemoryFact class
 * Faire des classes filles pour chaque type ?
 * Chaque fact dispose d'une bitset qui indiques quels sont les attributs que le fait a modifiés.
 * Utilisé comme test avant d'analyser plus en détail la requête
 *
 */
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

    MemoryFactType getFactType() const {return _factType;}
    float getFactBelief() const {return _factBelief;}

    // Getters & setters for attributes
    void setCharacterId(int characterId) {_characterId = characterId;}
    void setPosition(const Vec3Df& position) { _position = position;}

    int getCharacterId() const {return _characterId;}
    Vec3Df getPosition() const {return _position;} 
private:
    MemoryFactType _factType;
    float _factBelief;

    //Attributes
    Vec3Df  _position; 
    int _characterId;
    // To be continued...

};

}
#endif // MEMORYFACT_H
