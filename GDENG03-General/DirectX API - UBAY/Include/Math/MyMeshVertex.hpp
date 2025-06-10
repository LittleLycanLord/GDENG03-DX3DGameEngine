#pragma once
#include "Math/MyVector3.hpp"
#include "Math/MyVector2.hpp"

namespace DX3D {
    class MyMeshVertex {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        MyVector3 position;
        MyVector2 textureCoordinates;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMeshVertex() : position(),
            textureCoordinates() {
        }
        MyMeshVertex(MyVector3 position,
            MyVector2 textureCoordinates) : position(position),
            textureCoordinates(textureCoordinates) {
        }
        MyMeshVertex(const MyMeshVertex& other) : position(other.position), textureCoordinates(other.textureCoordinates) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:

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


