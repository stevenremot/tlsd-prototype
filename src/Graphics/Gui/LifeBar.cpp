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

#include "LifeBar.h"

#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>

namespace Graphics
{
    namespace Gui
    {
        void LifeBar::draw()
        {
            irr::video::IVideoDriver* driver = Environment->getVideoDriver();
                        const irr::s32 baseX = AbsoluteRect.UpperLeftCorner.X;
            const irr::s32 baseY = AbsoluteRect.UpperLeftCorner.Y;
            const irr::s32 baseW = AbsoluteRect.getWidth();
            const irr::s32 baseH = AbsoluteRect.getHeight();

            driver->draw2DRectangle(
                irr::video::SColor(128, 0, 0, 0),
                AbsoluteRect
            );

            const float ratio =
                static_cast<float>(currentHealth_) / static_cast<float>(maxHealth_);

            driver->draw2DRectangle(
                irr::video::SColor(255, 255, 0, 0),
                irr::core::rect<irr::s32>(
                    baseX,
                    baseY,
                    baseX + static_cast<float>(baseW) * ratio,
                    baseY + baseH
                )
            );

            driver->draw2DRectangleOutline(
                AbsoluteRect,
                irr::video::SColor(255, 255, 255, 255)
            );
        }
    }
}
