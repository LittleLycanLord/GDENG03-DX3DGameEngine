#pragma once

namespace DX3D {
    class Vec4 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float w{ 0.0f };
        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        Vec4() {};
        Vec4(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {};
        ~Vec4() {};

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

