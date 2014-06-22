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

#ifndef GRAPHICS_RENDER_SCENENODE_H
#define GRAPHICS_RENDER_SCENENODE_H

#include <list>
#include <irrlicht/ISceneNode.h>

#include "../../Geometry/Vec3D.h"

namespace Graphics
{
    namespace Render
    {
        /**
         * Class describing a node of the scene graph
         *
         */
        class SceneNode
        {
            public:
                SceneNode(const SceneNode* parent);
                virtual ~SceneNode();

                void addChild(SceneNode* child);

                void activateLight(bool b);
                void setFlatShading(bool b);

                irr::scene::ISceneNode* getIrrlichtSceneNode() const;
                void setIrrlichtSceneNode(irr::scene::ISceneNode* node);

                void setPosition(const Geometry::Vec3Df& pos);
                void setRotation(const Geometry::Vec3Df& rot);
                void setScale(const Geometry::Vec3Df& sca);
                void setAbsolutePosition(const Geometry::Vec3Df& pos);
                void setAbsoluteRotation(const Geometry::Vec3Df& rot);

                Geometry::Vec3Df getPosition() const;
                Geometry::Vec3Df getRotation() const;
                Geometry::Vec3Df getScale() const;
                Geometry::Vec3Df getAbsolutePosition() const;
                Geometry::Vec3Df getAbsoluteRotation() const;

                void setId(unsigned int id);

                unsigned int getId() const;

                const SceneNode* getParent() const;
                const std::list<SceneNode*>& getChildren() const;

                void removeChild(unsigned int id);
            protected:
                virtual void removeIrrlichtSceneNode();

                const SceneNode* parent_;
                std::list<SceneNode*> children_;
                unsigned int id_;
                irr::scene::ISceneNode* irrlichtSceneNode_;
            private:

        };
    }
}
#endif // GRAPHICS_RENDER_SCENENODE_H
