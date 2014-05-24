#include "Scene.h"

#include "MeshSceneNode.h"

// TODO: remove
#include <iostream>

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type InitSceneEvent::TYPE = "init_scene";

        Scene::Scene() :
            irrlichtSceneManager_(NULL),
            irrlichtVideoDriver_(NULL)
        {

        }

        Scene::~Scene()
        {
            // delete root scene node = delete all scene nodes
            delete sceneNodes_[0];
        }

        void Scene::call(const Event::Event& event)
        {
            const InitSceneEvent& e = static_cast<const InitSceneEvent&>(event);
            irrlichtSceneManager_ = e.getManager();
            irrlichtVideoDriver_ = e.getDriver();

            sceneNodes_.push_back(new SceneNode(NULL));
            sceneNodes_[0]->setIrrlichtSceneNode(irrlichtSceneManager_->getRootSceneNode());
            sceneNodes_[0]->setId(0);

            std::cout << "[Scene]: init done" << std::endl;
        }

        void Scene::run()
        {
            if (irrlichtSceneManager_ != NULL && irrlichtVideoDriver_ != NULL)
            {
                addMeshSceneNodeFromFile(sceneNodes_.back(), "ninja.b3d", "");
                sceneNodes_.back()->setPosition(Vec3Df(10,0,0));

                std::cout << "[Scene]: " << sceneNodes_.size() << " ninjas" << std::endl;
            }
        }

        void Scene::addMeshSceneNodeFromFile(SceneNode* parent, const string& meshFile, const string& textureFile)
        {
            irr::scene::IMeshSceneNode* irrNode = irrlichtSceneManager_->addMeshSceneNode(irrlichtSceneManager_->getMesh(meshFile.c_str()));
            if (parent != NULL)
                irrNode->setParent(parent->getIrrlichtSceneNode());

            MeshSceneNode* node = NULL;
            if (parent == NULL)
                node = new MeshSceneNode(sceneNodes_[0]);
            else
                node = new MeshSceneNode(parent);

            node->setIrrlichtSceneNode(irrNode);

            sceneNodes_.push_back(node);
            node->setId(sceneNodes_.size()-1);
            node->activateLight(false);

            parent->addChild(node);
        }
    }
}
