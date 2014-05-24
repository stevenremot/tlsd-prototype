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
                SceneNode(const SceneNode* parent);
                virtual ~SceneNode();

                void addChild(SceneNode* child);

                void activateLight(bool b);

                irr::scene::ISceneNode* getIrrlichtSceneNode() const;
                void setIrrlichtSceneNode(irr::scene::ISceneNode* node);

                void setPosition(const Vec3Df& pos);
                void setRotation(const Vec3Df& rot);
                void setScale(const Vec3Df& sca);

                Vec3Df getPosition() const;
                Vec3Df getRotation() const;
                Vec3Df getScale() const;

                void setId(unsigned int id);

                const unsigned int getId() const;

                const SceneNode* getParent() const;
                const std::list<SceneNode*>& getChildren() const;

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
