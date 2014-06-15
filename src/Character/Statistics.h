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

#ifndef CHARACTER_STATISTICS_H
#define CHARACTER_STATISTICS_H

#include "StatisticSlot.h"

namespace Character
{
    /**
     * Contains all entity's statistics.
     */
    class Statistics
    {
    public:
        Statistics(
            const StatisticSlot& health,
            const StatisticSlot& attack,
            const StatisticSlot& defense,
            const StatisticSlot& speed
        ):
            health_(health),
            attack_(attack),
            defense_(defense),
            speed_(speed)
        {}

        Statistics(const Statistics& stats):
            health_(stats.health_),
            attack_(stats.attack_),
            defense_(stats.defense_),
            speed_(stats.speed_)
        {}

        StatisticSlot& getHealth() { return health_; }
        const StatisticSlot& getHealth() const { return health_; }

        StatisticSlot& getAttack() { return attack_; }
        const StatisticSlot& getAttack() const { return attack_; }

        StatisticSlot& getDefense() { return defense_; }
        const StatisticSlot& getDefense() const { return defense_; }

        StatisticSlot& getSpeed() { return speed_; }
        const StatisticSlot& getSpeed() const { return speed_; }

    private:
        StatisticSlot health_;
        StatisticSlot attack_;
        StatisticSlot defense_;
        StatisticSlot speed_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
