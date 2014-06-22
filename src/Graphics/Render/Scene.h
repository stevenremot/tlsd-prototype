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

#ifndef GRAPHICS_RENDER_SCENE_H
#define GRAPHICS_RENDER_SCENE_H

#include <map>
#include <string>
#include <vector>
#include <irrlicht/ISceneManager.h>
#include <irrlicht/IVideoDriver.h>

#include "CameraSceneNode.h"
#include "Model3D.h"
#include "Animation.h"
#include "SceneData.h"
#include "Light.h"
#include "../../Event/Event.h"
#include "../../Event/EventListenerInterface.h"
#include "../../Event/ListenerRegister.h"
#include "../../Event/EventManager.h"
#include "../../Threading/ThreadableInterface.h"
#include "../../Ecs/Entity.h"

namespace Graphics
{
    namespace Render
    {
        /**
        *   Event provided by the Device to initialize the Scene object
        */
        class InitSceneEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            InitSceneEvent(irr::scene::ISceneManager* manager, irr::video::IVideoDriver* driver):
                Event::Event(Type),
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
         *  Represents the 3D Scene and manages its memory
         */
        class Scene : public Event::EventListenerInterface, public Threading::ThreadableInterface
        {
        public:
            Scene(Event::EventQueue& eventQueue);
            virtual ~Scene();

            // EventListener
            virtual void call(const Event::Event& event);

            // Threadable
            virtual void run();

            void registerListeners(Event::ListenerRegister& reg);

            bool initializeAnimationMap(const Ecs::Entity& entity, const AnimationMap& animationMap);

            void addCameraSceneNode(SceneNode* parent);
            void addLightSceneNode(SceneNode* parent, const Geometry::Vec3Df& position, const Light& light);
            void addMeshSceneNodeFromModel3D(
                SceneNode* parent,
                const Model3D& model3d,
                const Geometry::Vec3Df& position,
                const Geometry::Vec3Df& rotation
            );
            void addMeshSceneNodeFromFile(
                SceneNode* parent,
                const std::string& meshFile,
                const std::string& textureFile,
                const Geometry::Vec3Df& position,
                const Geometry::Vec3Df& rotation
            );
            void addAnimatedMeshSceneNodeFromFile(
                SceneNode* parent,
                const std::string& meshFile,
                const std::string& textureFile,
                const Geometry::Vec3Df& position,
                const Geometry::Vec3Df& rotation
            );
        protected:
        private:
            irr::scene::ISceneManager* irrlichtSceneManager_;
            irr::video::IVideoDriver* irrlichtVideoDriver_;

            const unsigned int verticesPerMeshBuffer_;
            SceneData data_;
            CameraSceneNode* camera_;

            Event::EventHead internEventHead_;
            Event::EventQueue internEventQueue_;
            Event::EventQueue& eventQueue_;
        };
    }
}
#endif // GRAPHICS_RENDER_SCENE_H
