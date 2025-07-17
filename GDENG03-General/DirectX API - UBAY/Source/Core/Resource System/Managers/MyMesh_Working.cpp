#include "Core/Resource System/Managers/MyMesh.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyHullShader.hpp"
#include "Graphics/Shaders/MyDomainShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Game/MyTransform.hpp"
#include "Game/Lighting/MyLight.hpp"
#include "Math/MyVector2.hpp"
#include "Math/MyVector3.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyMeshVertex.hpp"
#include "Math/MyConstant.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <cstring>

#define TINYOBJLOADER_IMPLEMENTATION
#include "Core/MyLogger.hpp"

using namespace DX3D;
extern const int MAX_LIGHTS;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMesh::MyMesh(const wchar_t* resourcePath) : transform(std::make_shared<MyTransform>()), attributes(),
shapes(),
materials(),
vertices(),
indices() {
    if (LOG_INFO_MESH) std::wcout << L"[INFO]: MyMesh constructed for " << resourcePath << std::endl;

    std::filesystem::path filePath = resourcePath;

    if (tinyobj::LoadObj(&this->attributes, &this->shapes, &this->materials, &this->warning, &this->error, filePath.string().c_str())) {
        {
            if (LOG_INFO_MESH) std::wcout << L"[INFO]: Loading MyMesh Vertices..." << std::endl;

            if (this->shapes.size() > 1) {
                std::cerr << "[ERROR]: Failed to load mesh from file" << std::endl;
                throw std::runtime_error("Failed to load mesh from file");
            }
            // Improved vertex processing with better variable names
            for (size_t shapeIndex = 0; shapeIndex < this->shapes.size(); shapeIndex++) {
                size_t indexOffset = 0;
                this->vertices.reserve(this->shapes[shapeIndex].mesh.indices.size());
                this->indices.reserve(this->shapes[shapeIndex].mesh.indices.size());

                for (size_t faceIndex = 0; faceIndex < this->shapes[shapeIndex].mesh.num_face_vertices.size(); faceIndex++) {
                    unsigned char verticesPerFace = this->shapes[shapeIndex].mesh.num_face_vertices[faceIndex];

                    for (unsigned char vertexIndex = 0; vertexIndex < verticesPerFace; vertexIndex++) {
                        //* Vertex Reading
                        tinyobj::index_t currentIndex = (tinyobj::index_t)this->shapes[shapeIndex].mesh.indices[indexOffset + vertexIndex];

                        //* POSITION
                        tinyobj::real_t positionX = 0, positionY = 0, positionZ = 0;
                        if (currentIndex.vertex_index >= 0) {
                            positionX = (tinyobj::real_t)this->attributes.vertices[currentIndex.vertex_index * 3 + 0];
                            positionY = (tinyobj::real_t)this->attributes.vertices[currentIndex.vertex_index * 3 + 1];
                            positionZ = (tinyobj::real_t)this->attributes.vertices[currentIndex.vertex_index * 3 + 2];
                        }

                        //* NORMAL
                        tinyobj::real_t normalX = 0, normalY = 0, normalZ = 0;
                        if (currentIndex.normal_index >= 0) {
                            normalX = (tinyobj::real_t)this->attributes.normals[currentIndex.normal_index * 3 + 0];
                            normalY = (tinyobj::real_t)this->attributes.normals[currentIndex.normal_index * 3 + 1];
                            normalZ = (tinyobj::real_t)this->attributes.normals[currentIndex.normal_index * 3 + 2];
                        }
                        else {
                            // Fallback: Generate a simple normal if not available
                            MyVector3 positionVector(positionX, positionY, positionZ);
                            float absX = std::abs(positionX);
                            float absY = std::abs(positionY);
                            float absZ = std::abs(positionZ);
                            float maxComponent = (absX > absY) ? ((absX > absZ) ? absX : absZ) : ((absY > absZ) ? absY : absZ);
                            if (maxComponent > 0) {
                                positionVector = positionVector * (1.0f / maxComponent); // Normalize to unit cube
                            }
                            normalX = positionVector.x;
                            normalY = positionVector.y;
                            normalZ = positionVector.z;
                        }

                        //* TEXCOORD
                        tinyobj::real_t textureU = 0, textureV = 0;
                        if (currentIndex.texcoord_index >= 0) {
                            textureU = (tinyobj::real_t)this->attributes.texcoords[currentIndex.texcoord_index * 2 + 0];
                            textureV = (tinyobj::real_t)this->attributes.texcoords[currentIndex.texcoord_index * 2 + 1];
                        }

                        this->vertices.push_back(MyMeshVertex(
                            MyVector3(positionX, positionY, positionZ),
                            MyVector3(normalX, normalY, normalZ),
                            MyVector2(textureU, textureV)
                        ));
                        this->indices.push_back((unsigned int)(indexOffset + vertexIndex));
                    }
                    indexOffset += verticesPerFace;
                }
            }
        }

        MyGraphicsEngine::GetInstance()->GetShaderByteCodeAndSize(&this->layoutShaderByteCode, &this->layoutShaderSize);
        this->vertexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexBuffer(&this->vertices[0], sizeof(MyMeshVertex), (UINT)this->vertices.size(), this->layoutShaderByteCode, this->layoutShaderSize);
        this->indexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateIndexBuffer(&this->indices[0], (UINT)this->indices.size());

        this->constantData.world = this->transform->worldMatrix; // Initial world matrix
        this->constantData.view.SetIdentity();                   // Set to identity or camera view
        this->constantData.projection.SetIdentity();             // Set to identity or camera projection
        this->constantData.time = 0.0f;                          // Initial time
        this->constantData.lightCount = 0;

        this->constantBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateConstantBuffer(&this->constantData, sizeof(MyConstant));
    }
    else {
        if (!this->error.empty())
            std::cerr << "[ERROR]: Failed to load mesh from file: " << this->error << std::endl;
        else
            std::cerr << "[ERROR]: Failed to load mesh from file" << std::endl;

        throw std::runtime_error("Failed to load mesh from file");
    }
}

MyMesh::~MyMesh() {
    if (LOG_INFO_MESH) std::cout << "[INFO]: MyMesh destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyMesh::Update(float deltaTime) {
    //* Transform Unit Test - TODO: Replace with proper transform system
    this->time += deltaTime;
    float circularMotionRadius = 3.0f;
    this->transform->position.x = circularMotionRadius * cosf(this->time);
    this->transform->position.z = circularMotionRadius * sinf(this->time);
    this->transform->rotation.y = this->time;
    this->transform->scale = MyVector3(1.0f + 0.5f * sinf(this->time)); // Pulsing scale effect

    this->transform->Update(deltaTime);
}

void MyMesh::Draw(MyVertexShaderPtr vertexShader, MyHullShaderPtr hullShader, MyDomainShaderPtr domainShader, MyPixelShaderPtr pixelShader,
    const MyMatrix4x4& viewMatrix, const MyMatrix4x4& projectionMatrix, float currentTime, const std::vector<MyLightPtr>& sceneLights) {

    // Update constant data
    this->constantData.world = this->transform->worldMatrix;
    this->constantData.view = viewMatrix;
    this->constantData.projection = projectionMatrix;
    this->constantData.time = currentTime;
    int lightCount = (int)sceneLights.size();
    this->constantData.lightCount = (lightCount < MAX_LIGHTS) ? lightCount : MAX_LIGHTS;

    if (sceneLights.size() > MAX_LIGHTS) {
        std::cout << "[WARNING]: Scene has " << sceneLights.size()
            << " lights, but only " << MAX_LIGHTS << " will be processed." << std::endl;
    }

    // Copy light data
    for (int lightIndex = 0; lightIndex < this->constantData.lightCount; ++lightIndex) {
        this->constantData.lights[lightIndex] = sceneLights[lightIndex]->ConvertToLightData();
    }

    // After copying lights, clear remaining slots to prevent garbage data
    for (int lightIndex = this->constantData.lightCount; lightIndex < MAX_LIGHTS; ++lightIndex) {
        memset(&this->constantData.lights[lightIndex], 0, sizeof(MyLightData));
    }

    // Update constant buffer
    MyDeviceContextPtr immediateDeviceContext = MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext();
    this->constantBuffer->Update(immediateDeviceContext, &this->constantData);

    // Set constant buffer for all shader stages
    immediateDeviceContext->SetConstantBuffer(vertexShader, this->constantBuffer);
    immediateDeviceContext->SetConstantBuffer(hullShader, this->constantBuffer);
    immediateDeviceContext->SetConstantBuffer(domainShader, this->constantBuffer);
    immediateDeviceContext->SetConstantBuffer(pixelShader, this->constantBuffer);

    // Set vertex and index buffers
    immediateDeviceContext->SetVertexBuffer(this->vertexBuffer);
    immediateDeviceContext->SetIndexBuffer(this->indexBuffer);

    // Draw
    immediateDeviceContext->DrawIndexedTriangles(this->indexBuffer->GetIndexCount(), 0, 0);
}
