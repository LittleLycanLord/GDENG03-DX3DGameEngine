#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include "Core/Primitives/MyTriangle.hpp"
#include "Math/MyVertex.hpp"

namespace DX3D {
    class MyCircle {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyTriangle triangles[16];
        MyVec3 bounceDirection;
        MyVec3 centerDelta;
        float radius = 0.1f;
        float xSpeed = 0.0f;
        float ySpeed = 0.0f;
        MyVertex top;
        MyVertex bottom;
        MyVertex left;
        MyVertex right;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyCircle();
        ~MyCircle();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Update(float deltaTime);

        std::vector<MyVertex> GetVertices() {
            std::vector<MyVertex> vertices;
            for (MyTriangle triangle : this->triangles)
                for (MyVertex vertex : triangle.GetVertices()) {
                    vertex.position *= this->radius;
                    vertex.position += this->centerDelta;
                    vertices.push_back(vertex);
                }
            return vertices;
        }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

