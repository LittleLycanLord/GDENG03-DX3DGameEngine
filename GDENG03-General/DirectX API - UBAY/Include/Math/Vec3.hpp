#pragma once

namespace DX3D {
    class Vec3 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        Vec3(){};
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
        ~Vec3() {};

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

