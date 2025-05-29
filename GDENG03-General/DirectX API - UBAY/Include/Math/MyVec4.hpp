#pragma once

namespace DX3D {
    class MyVec4 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x, y, z, w;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVec4() : x(0), y(0), z(0), w(0) {}
        MyVec4(float all) : x(all), y(all), z(all), w(all) {}
        MyVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        MyVec4(const MyVec4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

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


