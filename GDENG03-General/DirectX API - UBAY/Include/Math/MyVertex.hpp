#pragma once
#include "Math/MyVec3.hpp"

namespace DX3D {
    // // * Single Color Vertex
    // struct MyVertex {
    //     MyVec3 position;

    //     MyVertex() : position() {}
    //     MyVertex(float x, float y, float z) : position(x, y, z) {}
    //     MyVertex(const MyVec3& position) : position(position) {}
    // };

    // //* Colored Vertex
    // struct MyVertex {
    //     MyVec3 position;
    //     MyVec3 color;

    //     MyVertex() : position(0.0f), color(1.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), color(1.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b) {}
    //     MyVertex(const MyVec3& position) : position(position), color(1.0f) {}
    //     MyVertex(const MyVec3& position, const MyVec3& color) : position(position), color(color) {}
    // };

    // //* Animated Vertex : Moving
    // struct MyVertex {
    //     MyVec3 position;
    //     MyVec3 nextPosition;
    //     MyVec3 color;

    //     MyVertex() : position(0.0f), nextPosition(0.0f), color(1.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), nextPosition(position), color(1.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), nextPosition(position), color(r, g, b) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) : position(x1, y1, z1), nextPosition(x2, y2, z2), color(r, g, b) {}

    //     MyVertex(const MyVec3& position) : position(position), nextPosition(position), color(1.0f) {}
    //     MyVertex(const MyVec3& position, const MyVec3& color) : position(position), nextPosition(position), color(color) {}
    //     MyVertex(const MyVec3& position, const MyVec3& nextPosition, const MyVec3& color) : position(position), nextPosition(nextPosition), color(color) {}
    // };

    // //* Animated Vertex : Color Shifting
    // struct MyVertex {
    //     MyVec3 position;
    //     MyVec3 nextPosition;
    //     MyVec3 color;
    //     MyVec3 nextColor;

    //     MyVertex() : position(0.0f), nextPosition(0.0f), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), nextPosition(position), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), nextPosition(position), color(r, g, b), nextColor(0.0f) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) : position(x1, y1, z1), nextPosition(x2, y2, z2), color(r, g, b), nextColor(0.0f) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r1, float g1, float b1, float r2, float g2, float b2) : position(x1, y1, z1), nextPosition(x2, y2, z2), color(r1, g1, b1), nextColor(r2, g2, b2) {}

    //     MyVertex(const MyVec3& position) : position(position), nextPosition(position), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(const MyVec3& position, const MyVec3& color) : position(position), nextPosition(position), color(color), nextColor(0.0f) {}
    //     MyVertex(const MyVec3& position, const MyVec3& nextPosition, const MyVec3& color) : position(position), nextPosition(nextPosition), color(color), nextColor(0.0f) {}
    //     MyVertex(const MyVec3& position, const MyVec3& nextPosition, const MyVec3& color, const MyVec3& nextColor) : position(position), nextPosition(nextPosition), color(color), nextColor(nextColor) {}
    // };

    //* 3D Vertex
    struct MyVertex {
        MyVec3 position;
        MyVec3 color;
        MyVec3 nextColor;

        MyVertex() : position(0.0f), color(1.0f), nextColor(0.0f) {}
        MyVertex(float x, float y, float z) : position(x, y, z), color(1.0f), nextColor(0.0f) {}
        MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b), nextColor(0.0f) {}
        MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) : position(x1, y1, z1), color(r, g, b), nextColor(0.0f) {}
        MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r1, float g1, float b1, float r2, float g2, float b2) : position(x1, y1, z1), color(r1, g1, b1), nextColor(r2, g2, b2) {}

        MyVertex(const MyVec3& position) : position(position), color(1.0f), nextColor(0.0f) {}
        MyVertex(const MyVec3& position, const MyVec3& color) : position(position), color(color), nextColor(0.0f) {}
        MyVertex(const MyVec3& position, const MyVec3& nextPosition, const MyVec3& color) : position(position), color(color), nextColor(0.0f) {}
        MyVertex(const MyVec3& position, const MyVec3& nextPosition, const MyVec3& color, const MyVec3& nextColor) : position(position), color(color), nextColor(nextColor) {}
    };
} // namespace DX3D


