#pragma once
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Core/Resource System/Managers/MyMesh.hpp"

using namespace DX3D;

namespace DX3D {
    class MyMeshComponent : public MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyMeshPtr mesh;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
public:
        MyMeshComponent(const MyMeshPtr& mesh);
        virtual ~MyMeshComponent();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        MyMeshPtr GetMesh() const { return mesh; }
        void SetMesh(const MyMeshPtr& newMesh) { mesh = newMesh; }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
    };
} // namespace DX3D
