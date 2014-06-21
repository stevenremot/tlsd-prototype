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

#include "LightSceneNode.h"
#include "../../Geometry/IrrlichtConversions.h"

namespace Graphics
{
    namespace Render
    {
        irr::video::SColorf fromColor(const Color& color)
        {
            return irr::video::SColorf(color.getX(), color.getY(), color.getZ(), 1.0f);
        }

        irr::video::E_LIGHT_TYPE fromLightType(const LightType& type)
        {
            switch (type)
            {
            case Point:
                return irr::video::ELT_POINT;
            case Directional:
                return irr::video::ELT_DIRECTIONAL;
            case Spot:
                return irr::video::ELT_SPOT;
            default:
                return irr::video::ELT_POINT;
            }
        }

        LightSceneNode::LightSceneNode(const SceneNode& parent):
            SceneNode(parent)
        {
        }

        LightSceneNode::~LightSceneNode()
        {
            //dtor
        }

        void LightSceneNode::setIrrlichtSceneNode(irr::scene::ILightSceneNode* node)
        {
            irrlichtSceneNode_ = static_cast<irr::scene::ISceneNode*>(node);
        }

        void LightSceneNode::removeIrrlichtSceneNode()
        {
            static_cast<irr::scene::ILightSceneNode*>(irrlichtSceneNode_)->remove();
        }

        void LightSceneNode::setLight(const Light& light)
        {
            irr::video::SLight irrLight = irr::video::SLight();

            irrLight.Type = fromLightType(light.getType());
            irrLight.Radius = light.getRadius();
            irrLight.DiffuseColor = fromColor(light.getColor());

            irr::scene::ILightSceneNode* node
                = static_cast<irr::scene::ILightSceneNode*>(irrlichtSceneNode_);

            if (light.getType() == Directional)
                node->setRotation(Geometry::fromVec3Df(light.getDirection()).getHorizontalAngle());

            node->setLightData(irrLight);
        }
    }
}

