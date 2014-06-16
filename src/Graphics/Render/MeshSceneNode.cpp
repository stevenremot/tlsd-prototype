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

#include "MeshSceneNode.h"

namespace Graphics
{
    namespace Render
    {
        using irr::core::vector3df;

        MeshSceneNode::MeshSceneNode(const SceneNode& parent) :
            SceneNode(parent)
        {
            //ctor
        }

        MeshSceneNode::~MeshSceneNode()
        {

        }

        void MeshSceneNode::removeIrrlichtSceneNode()
        {
            dynamic_cast<irr::scene::IMeshSceneNode*>(irrlichtSceneNode_)->remove();
        }

        void MeshSceneNode::setIrrlichtSceneNode(irr::scene::IMeshSceneNode* node)
        {
            irrlichtSceneNode_ = dynamic_cast<irr::scene::ISceneNode*>(node);
        }

        irr::scene::IMesh* MeshSceneNode::getIrrlichtMesh() const
        {
            return static_cast<irr::scene::IMeshSceneNode*>(irrlichtSceneNode_)->getMesh();
        }
    }
}
