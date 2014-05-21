#ifndef GRAPHICS_RENDER_SCENENODE_H
#define GRAPHICS_RENDER_SCENENODE_H

#include <list>
#include <irrlicht/ISceneNode.h>

#include "../../Geometry/Vec3D.h"

namespace Graphics
{
    namespace Render
    {
        using Geometry::Vec3Df;

        /**
         * Class describing a node of the scene graph
         *
         */
        class SceneNode
        {
            public:
                SceneNode(const SceneNode& parent);
                virtual ~SceneNode();

            protected:
                Vec3Df getPosition() const;
                Vec3Df getRotation() const;
                Vec3Df getScale() const;

                const unsigned int getId() const;

                const SceneNode& getParent() const;
                const std::list<SceneNode*>& getChildren() const;

                const SceneNode& parent_;
                std::list<SceneNode*> children_;
                unsigned int id_;

            private:
                irr::scene::ISceneNode* irrlichtSceneNode_;
        };
    }
}
#endif // GRAPHICS_RENDER_SCENENODE_H
