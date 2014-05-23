#ifndef GRAPHICS_RENDER_SCENE_H
#define GRAPHICS_RENDER_SCENE_H

#include <vector>
#include <irrlicht/ISceneManager.h>

#include "SceneNode.h"

namespace Graphics
{
    namespace Render
    {
        /**
         *  Represent the 3D Scene and manages its memory
         */
        class Scene
        {
        public:
            Scene(irr::scene::ISceneManager* sceneManager);
            virtual ~Scene();

        protected:
        private:
            irr::scene::ISceneManager* irrlichtSceneManager_;
            SceneNode* rootSceneNode_;

            unsigned int currentMaxId_;
        };
    }
}
#endif // GRAPHICS_RENDER_SCENE_H
