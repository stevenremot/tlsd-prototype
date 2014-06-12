#include "Scene.h"

#include <irrlicht/SMesh.h>
#include <irrlicht/SMeshBuffer.h>

#include "AnimatedMeshSceneNode.h"

#include "ModelUtils.h"
#include "../../Input/Events.h"
#include "RenderEvents.h"
#include "AnimationEvents.h"
#include "../../Physics/EntityPositionChangedEvent.h"
#include "../../Physics/InitCollisionEngineEvent.h"

// TODO: remove
#include <iostream>

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type InitSceneEvent::TYPE = "init_scene";

        Scene::Scene(Event::EventQueue& eventQueue) :
            irrlichtSceneManager_(NULL),
            irrlichtVideoDriver_(NULL),
            verticesPerMeshBuffer_(10000),
            camera_(NULL),
            eventQueue_(eventQueue)
        {

        }

        Scene::~Scene()
        {
        }

        void Scene::registerListeners(Event::ListenerRegister& reg)
        {
            reg.put(Graphics::Render::InitSceneEvent::TYPE, this);
            reg.put(Input::CameraEvent::TYPE, this);
            reg.put(Graphics::Render::RenderMeshFileEvent::TYPE, this);
            reg.put(Graphics::Render::RenderModel3DEvent::TYPE, this);
            reg.put(Graphics::Render::RenderAnimatedMeshFileEvent::TYPE, this);
            reg.put(Graphics::Render::SetupAnimationEvent::TYPE, this);
            reg.put(Graphics::Render::AnimateEvent::TYPE, this);
            reg.put(Graphics::Render::UpdateAnimationEvent::TYPE, this);
            reg.put(Physics::EntityPositionChangedEvent::TYPE, this);
        }

        void Scene::call(const Event::Event& event)
        {
            if (event.getType() == InitSceneEvent::TYPE)
            {
                const InitSceneEvent& e = static_cast<const InitSceneEvent&>(event);
                irrlichtSceneManager_ = e.getManager();
                irrlichtVideoDriver_ = e.getDriver();

                // add root scene node
                SceneNode* root = new SceneNode(NULL);
                root->setIrrlichtSceneNode(irrlichtSceneManager_->getRootSceneNode());
                data_.addSceneNode(root);

                // init static camera
                addCameraSceneNode(data_.getRootSceneNode());
                camera_ = dynamic_cast<CameraSceneNode*>(data_.getLastSceneNode());
                camera_->initStaticCamera(Vec3Df(150,150,20), Vec3Df(0,0,0));

                eventQueue_ << new Physics::InitCollisionEngineEvent(irrlichtSceneManager_, &data_);

                std::cout << "[Scene]: init done" << std::endl;
            }
            else if (event.getType() == Input::CameraEvent::TYPE)
            {
                if (camera_ != NULL)
                {
                    events_ << new Input::CameraEvent(static_cast<const Input::CameraEvent&>(event));
                }
            }
            else if (event.getType() == RenderMeshFileEvent::TYPE)
            {
                events_ << new RenderMeshFileEvent(static_cast<const RenderMeshFileEvent&>(event));
            }
            else if (event.getType() == RenderAnimatedMeshFileEvent::TYPE)
            {
                events_ << new RenderAnimatedMeshFileEvent(static_cast<const RenderAnimatedMeshFileEvent&>(event));
            }
            else if (event.getType() == RenderModel3DEvent::TYPE)
            {
                events_ << new RenderModel3DEvent(static_cast<const RenderModel3DEvent&>(event));
            }
            else if (event.getType() == AnimateEvent::TYPE)
            {
                events_ << new AnimateEvent(static_cast<const AnimateEvent&>(event));
            }
            else if (event.getType() == SetupAnimationEvent::TYPE)
            {
                events_ << new SetupAnimationEvent(static_cast<const SetupAnimationEvent&>(event));
            }
            else if (event.getType() == UpdateAnimationEvent::TYPE)
            {
                events_ << new UpdateAnimationEvent(static_cast<const UpdateAnimationEvent&>(event));
            }
            else if (event.getType() == Physics::EntityPositionChangedEvent::TYPE)
            {
                events_ << new Physics::EntityPositionChangedEvent(static_cast<const Physics::EntityPositionChangedEvent&>(event));
            }

        }

        void Scene::run()
        {
            std::vector<Event::Event*> delayedEvents;

            while (!events_.isEmpty())
            {
                Event::Event* event = NULL;
                events_ >> event;

                if (event->getType() == Input::CameraEvent::TYPE)
                {
                    camera_->updateTarget(dynamic_cast<Input::CameraEvent*>(event)->getCursorPosition());
                }
                else if (event->getType() == RenderMeshFileEvent::TYPE)
                {
                    RenderMeshFileEvent* renderEvent = dynamic_cast<RenderMeshFileEvent*>(event);

                    if (irrlichtSceneManager_ != NULL && irrlichtVideoDriver_ != NULL)
                    {
                        addMeshSceneNodeFromFile(
                            NULL,
                            renderEvent->getMeshFile(),
                            renderEvent->getTextureFile(),
                            renderEvent->getPosition(),
                            renderEvent->getRotation()
                        );
                        data_.setLastSceneNodeEntity(renderEvent->getEntity());
                    }
                    else
                        delayedEvents.push_back(new RenderMeshFileEvent(*renderEvent));
                }
                else if (event->getType() == RenderAnimatedMeshFileEvent::TYPE)
                {
                    RenderAnimatedMeshFileEvent* renderEvent = dynamic_cast<RenderAnimatedMeshFileEvent*>(event);

                    if (irrlichtSceneManager_ != NULL && irrlichtVideoDriver_ != NULL)
                    {
                        addAnimatedMeshSceneNodeFromFile(
                            NULL,
                            renderEvent->getMeshFile(),
                            renderEvent->getTextureFile(),
                            renderEvent->getPosition(),
                            renderEvent->getRotation()
                        );
                        data_.setLastSceneNodeEntity(renderEvent->getEntity());
                    }
                    else
                        delayedEvents.push_back(new RenderAnimatedMeshFileEvent(*renderEvent));
                }
                else if (event->getType() == RenderModel3DEvent::TYPE)
                {
                    RenderModel3DEvent* renderEvent = dynamic_cast<RenderModel3DEvent*>(event);
                    if (irrlichtSceneManager_ != NULL && irrlichtVideoDriver_ != NULL)
                    {
                        addMeshSceneNodeFromModel3D(
                            NULL,
                            renderEvent->getModel(),
                            renderEvent->getPosition(),
                            renderEvent->getRotation()
                        );
                        data_.setLastSceneNodeEntity(renderEvent->getEntity());
                    }
                    else
                        delayedEvents.push_back(new RenderModel3DEvent(*renderEvent));
                }
                else if (event->getType() == SetupAnimationEvent::TYPE)
                {
                    SetupAnimationEvent* setupEvent = dynamic_cast<SetupAnimationEvent*>(event);
                    // delay this event while the scene node has not been initialized
                    if (!initializeAnimationMap(setupEvent->getEntity(), setupEvent->getAnimationMap()))
                        delayedEvents.push_back(new SetupAnimationEvent(*setupEvent));
                }
                else if (event->getType() == AnimateEvent::TYPE)
                {
                    AnimateEvent* animEvent = dynamic_cast<AnimateEvent*>(event);
                    SceneNode* entityNode = data_.getEntitySceneNode(animEvent->getEntity());
                    if (entityNode != NULL)
                    {
                        dynamic_cast<AnimatedMeshSceneNode*>(entityNode)->applyAnimation(animEvent->getAnimation());
                    }
                }
                else if (event->getType() == UpdateAnimationEvent::TYPE)
                {
                    UpdateAnimationEvent* animEvent = dynamic_cast<UpdateAnimationEvent*>(event);
                    SceneNode* entityNode = data_.getEntitySceneNode(animEvent->getEntity());
                    if (entityNode != NULL)
                    {
                        dynamic_cast<AnimatedMeshSceneNode*>(entityNode)->update();
                    }
                }
                else if (event->getType() == Physics::EntityPositionChangedEvent::TYPE)
                {
                    Physics::EntityPositionChangedEvent* posChangedEvent = dynamic_cast<Physics::EntityPositionChangedEvent*>(event);
                    SceneNode* entityNode = data_.getEntitySceneNode(posChangedEvent->getEntity());
                    if (entityNode != NULL)
                    {
                        entityNode->setAbsolutePosition(posChangedEvent->getPosition());
                    }
                }

                delete event;
            }

            for (unsigned int i =0; i < delayedEvents.size(); i++)
                events_ << delayedEvents[i];
        }

        void Scene::addMeshSceneNodeFromFile(
            SceneNode* parent,
            const string& meshFile,
            const string& textureFile,
            const Vec3Df& position,
            const Vec3Df& rotation)
        {
            irr::scene::IMeshSceneNode* irrNode = irrlichtSceneManager_->addMeshSceneNode(irrlichtSceneManager_->getMesh(meshFile.c_str()));
            if (parent != NULL)
                irrNode->setParent(parent->getIrrlichtSceneNode());

            MeshSceneNode* node = NULL;
            if (parent == NULL)
                node = new MeshSceneNode(data_.getRootSceneNode());
            else
                node = new MeshSceneNode(parent);

            node->setIrrlichtSceneNode(irrNode);

            data_.addSceneNode(node);
            node->activateLight(false);

            if (parent == NULL)
                data_.getRootSceneNode()->addChild(node);
            else
                parent->addChild(node);

            node->setAbsolutePosition(position);
            node->setAbsoluteRotation(rotation);
        }

        void Scene::addAnimatedMeshSceneNodeFromFile(
            SceneNode* parent,
            const string& meshFile,
            const string& textureFile,
            const Vec3Df& position,
            const Vec3Df& rotation)
        {
            irr::scene::IAnimatedMeshSceneNode* irrNode = irrlichtSceneManager_->addAnimatedMeshSceneNode(irrlichtSceneManager_->getMesh(meshFile.c_str()));
            if (parent != NULL)
                irrNode->setParent(parent->getIrrlichtSceneNode());

            AnimatedMeshSceneNode* node = NULL;
            if (parent == NULL)
                node = new AnimatedMeshSceneNode(data_.getRootSceneNode());
            else
                node = new AnimatedMeshSceneNode(parent);

            node->setIrrlichtSceneNode(irrNode);

            data_.addSceneNode(node);
            node->activateLight(false);

            if (parent == NULL)
                data_.getRootSceneNode()->addChild(node);
            else
                parent->addChild(node);

            node->setAbsolutePosition(position);
            node->setAbsoluteRotation(rotation);
        }

        void Scene::addMeshSceneNodeFromModel3D(
            SceneNode* parent,
            const Model3D& model,
            const Vec3Df& position,
            const Vec3Df& rotation)
        {
            using irr::scene::SMeshBuffer;
            using irr::core::vector3df;
            using irr::video::S3DVertex;

            // compute the model's normals
            std::vector<Vec3Df> normals;
            computeNormals(model, normals);

            // build the mesh
            unsigned int bufferNumber = 1 + model.getVertices().size() / verticesPerMeshBuffer_;
            unsigned int trianglesPerMeshBuffer = verticesPerMeshBuffer_/2;

            irr::scene::SMesh* mesh = new irr::scene::SMesh();
            irr::scene::SMeshBuffer* currentMeshBuffer = NULL;

            for (unsigned int buffer = 0; buffer < bufferNumber; buffer++)
            {
                if (buffer < mesh->getMeshBufferCount())
                    currentMeshBuffer = dynamic_cast<SMeshBuffer*>(mesh->getMeshBuffer(buffer));
                else
                {
                    currentMeshBuffer = new SMeshBuffer();
                    mesh->addMeshBuffer(currentMeshBuffer);
                    currentMeshBuffer->drop();
                }

                unsigned int currentVerticeNumber = verticesPerMeshBuffer_;
                unsigned int currentTriangleNumber = verticesPerMeshBuffer_/2;

                if (buffer == bufferNumber-1)
                {
                    currentVerticeNumber = model.getVertices().size() - (bufferNumber-1)*verticesPerMeshBuffer_;
                    currentTriangleNumber = model.getFaces().size() - (bufferNumber-1)*verticesPerMeshBuffer_/2;
                }

                currentMeshBuffer->Vertices.set_used(currentVerticeNumber);
                currentMeshBuffer->Indices.set_used(currentTriangleNumber*3);

                for (unsigned int i = 0; i < currentVerticeNumber; i++)
                {
                    const Vec3Df& v = model.getVertices()[buffer*verticesPerMeshBuffer_+i];
                    const Vec3Df& n = normals[buffer*verticesPerMeshBuffer_+i];

                    S3DVertex& irrVertex = currentMeshBuffer->Vertices[i];
                    irrVertex.Pos.set(v.getX(), v.getZ(), v.getY());
                    irrVertex.Normal.set(n.getX(), n.getZ(), n.getY());
                    irrVertex.TCoords.set(v.getX()/512.0f, v.getY()/512.0f);
                }

                for (unsigned int t = 0; t < currentTriangleNumber; t++)
                {
                    const Face& face = model.getFaces()[buffer*trianglesPerMeshBuffer + t];

                    currentMeshBuffer->Indices[3*t] = face[0] - buffer*verticesPerMeshBuffer_;
                    currentMeshBuffer->Indices[3*t+1] = face[1] - buffer*verticesPerMeshBuffer_;
                    currentMeshBuffer->Indices[3*t+2] = face[2] - buffer*verticesPerMeshBuffer_;

                    unsigned int r = static_cast<unsigned int>(255.0f*face.getColor().getX());
                    unsigned int g = static_cast<unsigned int>(255.0f*face.getColor().getY());
                    unsigned int b = static_cast<unsigned int>(255.0f*face.getColor().getZ());

                    currentMeshBuffer->Vertices[-buffer*verticesPerMeshBuffer_+face[0]].Color.set(255, r, g, b);
                    currentMeshBuffer->Vertices[-buffer*verticesPerMeshBuffer_+face[1]].Color.set(255, r, g, b);
                    currentMeshBuffer->Vertices[-buffer*verticesPerMeshBuffer_+face[2]].Color.set(255, r, g, b);
                }

                currentMeshBuffer->recalculateBoundingBox();
            }

            // clean memory if needed
            if (bufferNumber < mesh->getMeshBufferCount())
                for (unsigned int i = bufferNumber; i < mesh->getMeshBufferCount()-bufferNumber; i++)
                    mesh->getMeshBuffer(i)->drop();

            mesh->MeshBuffers.erase(bufferNumber, mesh->getMeshBufferCount()-bufferNumber);

            // set dirty flag to make sure that hardware copies of this
            // buffer are also updated, see IMesh::setHardwareMappingHint
            mesh->setDirty();
            mesh->recalculateBoundingBox();

            mesh->setHardwareMappingHint(irr::scene::EHM_STATIC, irr::scene::EBT_VERTEX_AND_INDEX);

            // create the scene node
            irr::scene::IMeshSceneNode* irrNode = irrlichtSceneManager_->addMeshSceneNode(mesh);
            if (parent != NULL)
                irrNode->setParent(parent->getIrrlichtSceneNode());

            MeshSceneNode* node = NULL;
            if (parent == NULL)
                node = new MeshSceneNode(data_.getRootSceneNode());
            else
                node = new MeshSceneNode(parent);

            node->setIrrlichtSceneNode(irrNode);

            data_.addSceneNode(node);
            node->activateLight(false);
            node->setFlatShading(true);

            if (parent == NULL)
                data_.getRootSceneNode()->addChild(node);
            else
                parent->addChild(node);

            node->setAbsolutePosition(position);
            node->setAbsoluteRotation(rotation);
        }

        void Scene::addCameraSceneNode(SceneNode* parent)
        {
            irr::scene::ICameraSceneNode* irrNode = irrlichtSceneManager_->addCameraSceneNode();
            if (parent != NULL)
                irrNode->setParent(parent->getIrrlichtSceneNode());

            CameraSceneNode* node = NULL;
            if (parent == NULL)
                node = new CameraSceneNode(data_.getRootSceneNode());
            else
                node = new CameraSceneNode(parent);

            node->setIrrlichtSceneNode(irrNode);

            data_.addSceneNode(node);

            parent->addChild(node);
        }

        bool Scene::initializeAnimationMap(const Ecs::Entity& entity, const AnimationMap& animationMap)
        {
            SceneNode* entityNode = data_.getEntitySceneNode(entity);
            if (entityNode == NULL)
                return false;
            else
            {
                dynamic_cast<AnimatedMeshSceneNode*>(entityNode)->setAnimationMap(animationMap);
                return true;
            }
        }
    }
}
