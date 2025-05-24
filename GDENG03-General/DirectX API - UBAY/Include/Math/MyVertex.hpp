#pragma once
#include "Math/MyVec3.hpp"

namespace DX3D {
    //* Single Color Vertex
    // namespace DX3D {
    //     struct MyVertex {
    //         MyVec3 position;

    //         MyVertex() : position() {}
    //         MyVertex(float x, float y, float z) : position(x, y, z) {}
    //         MyVertex(const MyVec3& position) : position(position) {}
    //     };
    // } // namespace DX3D

    //* Colored Vertex
    struct MyVertex {
        MyVec3 position;
        MyVec3 color;

        MyVertex() : position(0.0f), color(1.0f) {}
        MyVertex(float x, float y, float z) : position(x, y, z), color(1.0f) {}
        MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b) {}
        MyVertex(const MyVec3& position) : position(position), color(1.0f) {}
        MyVertex(const MyVec3& position, const MyVec3& color) : position(position), color(color) {}
    };
} // namespace DX3D


