#include "Scene.h"

#include <irrlicht/SMesh.h>
#include <irrlicht/SMeshBuffer.h>

#include "MeshSceneNode.h"

#include "ModelUtils.h"

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
            verticesPerMeshBuffer_(10000)
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
                Model3D cube = createCubeModel(Color(1.0f, 0.0f, 0.0f));
                addMeshSceneNodeFromModel3D(sceneNodes_.back(), cube);

                //addMeshSceneNodeFromFile(sceneNodes_.back(), "ninja.b3d", "");
                sceneNodes_.back()->setPosition(Vec3Df(5,0,0));
                //sceneNodes_.back()->setScale(Vec3Df(3,3,3));

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

        void Scene::addMeshSceneNodeFromModel3D(SceneNode* parent, const Model3D& model)
        {
            using irr::scene::SMeshBuffer;
            using irr::core::vector3df;
            using irr::video::S3DVertex;

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

                    S3DVertex& irrVertex = currentMeshBuffer->Vertices[i];
                    irrVertex.Pos.set(v.getX(), v.getY(), v.getZ());
                    irrVertex.Normal.set(1,1,1);
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
    }
}
