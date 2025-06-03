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
        void Cross(MyVec4& A, MyVec4& B, MyVec4& C) {
            this->x = A.y * (B.z * C.w - C.z * B.w) - A.z * (B.y * C.w - C.y * B.w) + A.w * (B.y * C.z - B.z * C.y);
            this->y = -(A.x * (B.z * C.w - C.z * B.w) - A.z * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.z - C.x * B.z));
            this->z = A.x * (B.y * C.w - C.y * B.w) - A.y * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.y - C.x * B.y);
            this->w = -(A.x * (B.y * C.z - C.y * B.z) - A.y * (B.x * C.z - C.x * B.z) + A.z * (B.x * C.y - C.x * B.y));
        }
        MyVec4 GetCross(MyVec4& A, MyVec4& B, MyVec4& C) {
            MyVec4 result(this->x, this->y, this->z, this->w);
            result.x = A.y * (B.z * C.w - C.z * B.w) - A.z * (B.y * C.w - C.y * B.w) + A.w * (B.y * C.z - B.z * C.y);
            result.y = -(A.x * (B.z * C.w - C.z * B.w) - A.z * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.z - C.x * B.z));
            result.z = A.x * (B.y * C.w - C.y * B.w) - A.y * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.y - C.x * B.y);
            result.w = -(A.x * (B.y * C.z - C.y * B.z) - A.y * (B.x * C.z - C.x * B.z) + A.z * (B.x * C.y - C.x * B.y));
            return result;
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


