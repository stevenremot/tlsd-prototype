#include "Scene.h"

#include <irrlicht/SMesh.h>
#include <irrlicht/SMeshBuffer.h>

#include "MeshSceneNode.h"

#include "ModelUtils.h"
#include "../../Input/Events.h"

// TODO: remove
#include <iostream>

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type InitSceneEvent::TYPE = "init_scene";

        Scene::Scene() :
            irrlichtSceneManager_(NULL),
            irrlichtVideoDriver_(NULL),
            verticesPerMeshBuffer_(10000),
            camera_(NULL)
        {

        }

        Scene::~Scene()
        {
            // delete root scene node => delete all scene nodes
            delete sceneNodes_[0];
        }

        void Scene::call(const Event::Event& event)
        {
            if (event.getType() == InitSceneEvent::TYPE)
            {
                const InitSceneEvent& e = static_cast<const InitSceneEvent&>(event);
                irrlichtSceneManager_ = e.getManager();
                irrlichtVideoDriver_ = e.getDriver();

                // add root scene node
                sceneNodes_.push_back(new SceneNode(NULL));
                sceneNodes_[0]->setIrrlichtSceneNode(irrlichtSceneManager_->getRootSceneNode());
                sceneNodes_[0]->setId(0);

                Model3D cube = createCubeModel(Color(1.0f, 0.0f, 0.0f));
                addMeshSceneNodeFromModel3D(sceneNodes_.back(), cube);

                // init camera
                addCameraSceneNode(sceneNodes_.back());
                camera_ = dynamic_cast<CameraSceneNode*>(sceneNodes_.back());
                camera_->initPositionAndTarget();

                std::cout << "[Scene]: init done" << std::endl;
            }
            else if (event.getType() == Input::CameraEvent::TYPE)
            {
                if (camera_ != NULL)
                {
                    events_ << new Input::CameraEvent(static_cast<const Input::CameraEvent&>(event));
                    //camera_->updateTarget(static_cast<const Input::CameraEvent&>(event).getCursorPosition());
                }
            }

        }

        void Scene::run()
        {
            std::cout << "[Scene]: running " << std::time(NULL) << std::endl;

            if (irrlichtSceneManager_ != NULL && irrlichtVideoDriver_ != NULL)
            {
                Model3D cube = createCubeModel(Color(1.0f, 0.0f, 0.0f));
                addMeshSceneNodeFromModel3D(sceneNodes_.back(), cube);

                //addMeshSceneNodeFromFile(sceneNodes_.back(), "ninja.b3d", "");
                sceneNodes_.back()->setPosition(Vec3Df(5,0,0));
                //sceneNodes_.back()->setScale(Vec3Df(3,3,3));

                //std::cout << "[Scene]: " << sceneNodes_.size() << " ninjas" << std::endl;
            }

            while (!events_.isEmpty())
            {
                Event::Event* event = NULL;
                events_ >> event;

                if (event->getType() == Input::CameraEvent::TYPE)
                {
                    camera_->updateTarget(dynamic_cast<Input::CameraEvent*>(event)->getCursorPosition());
                }

                delete event;
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

        void Scene::addMeshSceneNodeFromModel3D(SceneNode* parent, const Model3D& model)
        {
            using irr::scene::SMeshBuffer;
            using irr::core::vector3df;
            using irr::video::S3DVertex;

            // compute the model's normals
            std::vector<Vec3Df> normals;
            computeNormals(model, normals);

            // build the mesh
            unsigned int bufferNumber = 1 + model.getVertices().size() / verticesPerMeshBuffer_;

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
                    const Vec3Df& v = model.getVertices()[(bufferNumber-1)*verticesPerMeshBuffer_+i];
                    const Vec3Df& n = normals[(bufferNumber-1)*verticesPerMeshBuffer_+i];

                    S3DVertex& irrVertex = currentMeshBuffer->Vertices[i];
                    irrVertex.Pos.set(v.getX(), v.getY(), v.getZ());
                    irrVertex.Normal.set(n.getX(), n.getY(), n.getZ());
                    irrVertex.TCoords.set(v.getX()/512.0f, v.getY()/512.0f);
                }

                for (unsigned int t = 0; t < currentTriangleNumber; t++)
                {
                    const Face& face = model.getFaces()[t];

                    currentMeshBuffer->Indices[3*t] = face[0];
                    currentMeshBuffer->Indices[3*t+1] = face[1];
                    currentMeshBuffer->Indices[3*t+2] = face[2];

                    unsigned int r = static_cast<unsigned int>(255.0f*face.getColor().getX());
                    unsigned int g = static_cast<unsigned int>(255.0f*face.getColor().getY());
                    unsigned int b = static_cast<unsigned int>(255.0f*face.getColor().getZ());

                    currentMeshBuffer->Vertices[(bufferNumber-1)*verticesPerMeshBuffer_+face[0]].Color.set(255, r, g, b);
                    currentMeshBuffer->Vertices[(bufferNumber-1)*verticesPerMeshBuffer_+face[1]].Color.set(255, r, g, b);
                    currentMeshBuffer->Vertices[(bufferNumber-1)*verticesPerMeshBuffer_+face[2]].Color.set(255, r, g, b);
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

            // create the scene node
            irr::scene::IMeshSceneNode* irrNode = irrlichtSceneManager_->addMeshSceneNode(mesh);
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

        void Scene::addCameraSceneNode(SceneNode* parent)
        {
            irr::scene::ICameraSceneNode* irrNode = irrlichtSceneManager_->addCameraSceneNode();
            if (parent != NULL)
                irrNode->setParent(parent->getIrrlichtSceneNode());

            CameraSceneNode* node = NULL;
            if (parent == NULL)
                node = new CameraSceneNode(sceneNodes_[0]);
            else
                node = new CameraSceneNode(parent);

            node->setIrrlichtSceneNode(irrNode);

            sceneNodes_.push_back(node);
            node->setId(sceneNodes_.size()-1);

            parent->addChild(node);
        }
    }
}
