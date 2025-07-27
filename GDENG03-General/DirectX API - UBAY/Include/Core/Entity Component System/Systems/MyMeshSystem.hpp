#pragma once
#include "Core/Entity Component System/Systems/MySystem.hpp"
#include "Core/Entity Component System/Components/MyMeshComponent.hpp"
#include "Core/Entity Component System/Components/MyTransformComponent.hpp"

namespace DX3D {
    class MyMeshSystem : public MySystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        // No extra attributes for now
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMeshSystem() = default;
        virtual ~MyMeshSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Update all entities with a mesh and transform (ECS logic only)
        virtual void Update(float deltaTime) override;

        // Render all mesh entities (ECS rendering)
        void RenderMeshes(
            MyVertexShaderPtr vertexShader,
            MyHullShaderPtr hullShader,
            MyDomainShaderPtr domainShader,
            MyPixelShaderPtr pixelShader,
            const MyMatrix4x4& cameraWorldMatrix,
            const MyMatrix4x4& cameraProjectionMatrix,
            float time
        );

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
    };
} // namespace DX3D
