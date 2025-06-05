#pragma once

namespace DX3D {
    class MyVec2 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x, y;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVec2() : x(0), y(0) {}
        MyVec2(float all) : x(all), y(all) {}
        MyVec2(float x, float y) : x(x), y(y) {}
        MyVec2(const MyVec2& other) : x(other.x), y(other.y) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MyVec2 operator * (float scalar) const {
            return MyVec2(this->x * scalar, this->y * scalar);
        }
        MyVec2 operator + (MyVec2 other) const {
            return MyVec2(this->x + other.x, this->y + other.y);
        }
        MyVec2& operator += (const MyVec2& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }
        static MyVec2 Lerp(const MyVec2& start, const MyVec2& end, float delta) {
            MyVec2 returnVector;
            returnVector.x = start.x * (1.0f - delta) + end.x * (delta);
            returnVector.y = start.y * (1.0f - delta) + end.y * (delta);
            return returnVector;
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


