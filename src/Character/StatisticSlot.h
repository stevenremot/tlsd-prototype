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

#ifndef CHARACTER_STATISTIC_SLOT_H
#define CHARACTER_STATISTIC_SLOT_H

#include <algorithm>

namespace Character
{
    /**
     * A slot for one statistic characteristic (health, attack, etc...)
     */
    class StatisticSlot
    {
    public:
        StatisticSlot(unsigned int baseValue):
            baseValue_(baseValue),
            currentValue_(baseValue)
        {}

        StatisticSlot(const StatisticSlot& slot):
            baseValue_(slot.baseValue_),
            currentValue_(slot.currentValue_)
        {}

        unsigned int getBaseValue() const { return baseValue_; }
        void setBaseValue(unsigned int baseValue)
        {
            baseValue_ = baseValue;
        }

        unsigned int getCurrentValue() const { return currentValue_; }
        void setCurrentValue(unsigned int currentValue)
        {
            currentValue_ = std::min(baseValue_, currentValue);
        }

        void addToValue(int diff)
        {
            int cur = currentValue_;
            if (-diff > cur)
            {
                currentValue_ = 0;
            }
            else
            {
                setCurrentValue(cur + diff);
            }
        }

    private:
        unsigned int baseValue_;
        unsigned int currentValue_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
