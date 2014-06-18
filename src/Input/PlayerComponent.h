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

#ifndef INPUT_PLAYER_COMPONENT_H
#define INPUT_PLAYER_COMPONENT_H

#include "../Ecs/Component.h"
#include "../Graphics/Render/CameraSceneNode.h"

namespace Input
{
    /**
     * Component tagging an entity as the player.
     */
    class PlayerComponent: public Ecs::Component
    {
    public:
        static const Type Type;
        PlayerComponent():
            Component(Type),
            camera_(NULL)
        {}

        virtual const std::vector<Component::Type>& getDependentComponents();

        Graphics::Render::CameraSceneNode& getCamera()
        {
            return *camera_;
        }
        const Graphics::Render::CameraSceneNode& getCamera() const
        {
            return *camera_;
        }

        void setCamera(Graphics::Render::CameraSceneNode* camera)
        {
            camera_ = camera;
        }

        bool isCameraSet() const
        {
            return camera_ != NULL;
        }


    private:
        static std::vector<Component::Type> dependantComponents_;
        Graphics::Render::CameraSceneNode* camera_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
