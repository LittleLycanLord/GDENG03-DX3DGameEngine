#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include "Core/Primitives/MyQuad.hpp"
#include "Math/MyVertex.hpp"

namespace DX3D {
    class MyCube {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyQuad faces[6];
        float size = 0.5f;
        MyVec3 position;
        MyVec3 rotation;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyCube();
        ~MyCube();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        std::vector<MyVertex> GetVertices() {
            std::vector<MyVertex> vertices;
            for (MyQuad face : this->faces)
                for (MyVertex vertex : face.GetVertices()) {
                    vertex.position *= this->size;
                    vertex.position += this->position;
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

