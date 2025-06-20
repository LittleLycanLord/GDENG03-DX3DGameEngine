#pragma once

namespace DX3D {
    class MyVec3 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x, y, z;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVec3() : x(0), y(0), z(0) {}
        MyVec3(float all) : x(all), y(all), z(all) {}
        MyVec3(float x, float y, float z) : x(x), y(y), z(z) {}
        MyVec3(const MyVec3& other) : x(other.x), y(other.y), z(other.z) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        static MyVec3 Lerp(const MyVec3& start, const MyVec3& end, float delta) {
            MyVec3 returnVector;
            returnVector.x = start.x * (1.0f - delta) + end.x * (delta);
            returnVector.y = start.y * (1.0f - delta) + end.y * (delta);
            returnVector.z = start.z * (1.0f - delta) + end.z * (delta);
            return returnVector;
        }
        MyVec3& operator*=(const float& scalar) {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        MyVec3& operator+=(const MyVec3& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
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


