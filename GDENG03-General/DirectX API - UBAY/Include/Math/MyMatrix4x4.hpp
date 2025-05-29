#pragma once
#include "Math/MyVec3.hpp"
#include "memory"

namespace DX3D {
    class MyMatrix4x4 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float matrix[4][4];

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMatrix4x4() { this->SetIdentity(); }
        ~MyMatrix4x4() {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void SetIdentity() {
            memset(matrix, 0, sizeof(float) * 16);
            matrix[0][0] = 1;
            matrix[1][1] = 1;
            matrix[2][2] = 1;
            matrix[3][3] = 1;
        }

        void Translate(const MyVec3& translation) {
            this->SetIdentity();
            matrix[3][0] = translation.x;
            matrix[3][1] = translation.y;
            matrix[3][2] = translation.z;
        }
        void Scale(const MyVec3& scale) {
            this->SetIdentity();
            matrix[0][0] = scale.x;
            matrix[1][1] = scale.y;
            matrix[2][2] = scale.z;
        }
        void SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            this->SetIdentity();
            matrix[0][0] = 2.0f / width;
            matrix[1][1] = 2.0f / height;
            matrix[2][2] = 1.0f / (farPlane - nearPlane);
            matrix[3][3] = -(nearPlane / (farPlane - nearPlane));
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

