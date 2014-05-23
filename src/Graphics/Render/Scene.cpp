#include "Scene.h"

namespace Graphics
{
    namespace Render
    {
        Scene::Scene(irr::scene::ISceneManager* sceneManager) :
            irrlichtSceneManager_(sceneManager)
        {
            rootSceneNode_ = new SceneNode(NULL);
            rootSceneNode_->setIrrlichtSceneNode(irrlichtSceneManager_->getRootSceneNode());

            currentMaxId_ = 1;
        }

        Scene::~Scene()
        {
            //dtor
        }
    }
}
