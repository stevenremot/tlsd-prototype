#ifndef GRAPHICS_RENDER_SCENE_H
#define GRAPHICS_RENDER_SCENE_H

#include <map>
#include <string>
#include <vector>
#include <irrlicht/ISceneManager.h>
#include <irrlicht/IVideoDriver.h>

#include "SceneNode.h"
#include "Model3D.h"
#include "../../Event/Event.h"
#include "../../Event/EventListenerInterface.h"
#include "../../Threading/ThreadableInterface.h"

namespace Graphics
{
    namespace Render
    {
        using std::string;
        using std::map;
        using std::vector;

        /**
        *   Event provided by the Device to initialize the Scene object
        */
        class InitSceneEvent : public Event::Event
        {
        public:
            static const Event::Type TYPE;

            InitSceneEvent(irr::scene::ISceneManager* manager, irr::video::IVideoDriver* driver):
                Event::Event(TYPE),
                manager_(manager),
                driver_(driver)
            {}

            irr::scene::ISceneManager* getManager() const
            {
                return manager_;
            }

            irr::video::IVideoDriver* getDriver() const
            {
                return driver_;
            }

        private:
            irr::scene::ISceneManager* manager_;
            irr::video::IVideoDriver* driver_;
        };


        /**
         *  Represent the 3D Scene and manages its memory
         */
        class Scene : public Event::EventListenerInterface, public Threading::ThreadableInterface
        {
        public:
            Scene();
            virtual ~Scene();

            // EventListener
            virtual void call(const Event::Event& event);

            // Threadable
            virtual void run();

            void addMeshSceneNodeFromModel3D(SceneNode* parent, const Model3D& model3d);
            void addMeshSceneNodeFromFile(SceneNode* parent, const string& meshFile, const string& textureFile);
        protected:
        private:
            irr::scene::ISceneManager* irrlichtSceneManager_;
            irr::video::IVideoDriver* irrlichtVideoDriver_;

            /*
            *   For direct access to scene node by its id
            */
            vector<SceneNode*> sceneNodes_;
        };
    }
}
#endif // GRAPHICS_RENDER_SCENE_H
