#include "Core/Entity Component System/Components/MyTransformComponent.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyTransformComponent::MyTransformComponent() : transform(std::make_shared<MyTransform>()) {}
MyTransformComponent::MyTransformComponent(MyTransformPtr t) : transform(t) {}
MyTransformComponent::~MyTransformComponent() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyTransformComponent::Update(float deltaTime) { if (transform) transform->Update(deltaTime); }

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
