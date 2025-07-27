#include "Core/Entity Component System/Systems/MyMeshSystem.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMeshSystem::~MyMeshSystem() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyMeshSystem::Update(float deltaTime) {}
void MyMeshSystem::RenderMeshes(
    MyVertexShaderPtr vertexShader,
    MyHullShaderPtr hullShader,
    MyDomainShaderPtr domainShader,
    MyPixelShaderPtr pixelShader,
    const MyMatrix4x4& cameraWorldMatrix,
    const MyMatrix4x4& cameraProjectionMatrix,
    float time
) {
    for (const auto& entity : GetEntities()) {
        auto meshComp = entity->GetComponent<MyMeshComponent>();
        auto transformComp = entity->GetComponent<MyTransformComponent>();
        if (meshComp && transformComp) {
            meshComp->GetMesh()->transform = transformComp->GetTransform();

            meshComp->GetMesh()->Draw(
                vertexShader,
                hullShader,
                domainShader,
                pixelShader,
                cameraWorldMatrix,
                cameraProjectionMatrix,
                time
            );
        }
    }
}


//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
