#pragma once
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Game/MyTransform.hpp"

using namespace DX3D;

namespace DX3D {
    class MyTransformComponent : public MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        MyTransformPtr transform;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyTransformComponent();
        MyTransformComponent(MyTransformPtr t);
        virtual ~MyTransformComponent();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        void Update(float deltaTime);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        MyTransformPtr GetTransform() { return transform; }
        void SetTransform(MyTransformPtr newTransform) { transform = newTransform; }
    };
} // namespace DX3D
