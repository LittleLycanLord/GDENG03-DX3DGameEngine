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
            memset(this->matrix, 0, sizeof(float) * 16);
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
            matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
        }

        // Matrix multiplication
        MyMatrix4x4 operator *(const MyMatrix4x4& rhs) const {
            MyMatrix4x4 result;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j) {
                    result.matrix[i][j] = 0.0f;
                    for (int k = 0; k < 4; ++k)
                        result.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
                }
            return result;
        }

        MyMatrix4x4& operator*=(const MyMatrix4x4& rhs) {
            *this = *this * rhs;
            return *this;
        }

        MyVec3 DotProduct(const MyVec3& v) const {
            float x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0] + matrix[3][0];
            float y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1] + matrix[3][1];
            float z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2] + matrix[3][2];
            return MyVec3(x, y, z);
        }
        void Transpose() {
            for (int i = 0; i < 4; ++i)
                for (int j = i + 1; j < 4; ++j)
                    std::swap(matrix[i][j], matrix[j][i]);
        }

        static MyMatrix4x4 Identity() {
            MyMatrix4x4 m;
            m.SetIdentity();
            return m;
        }
        static MyMatrix4x4 Translation(const MyVec3& t) {
            MyMatrix4x4 m;
            m.SetIdentity();
            m.matrix[3][0] = t.x;
            m.matrix[3][1] = t.y;
            m.matrix[3][2] = t.z;
            return m;
        }
        static MyMatrix4x4 Scaling(const MyVec3& s) {
            MyMatrix4x4 m;
            m.SetIdentity();
            m.matrix[0][0] = s.x;
            m.matrix[1][1] = s.y;
            m.matrix[2][2] = s.z;
            return m;
        }
        static MyMatrix4x4 OrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            MyMatrix4x4 m;
            m.SetIdentity();
            m.matrix[0][0] = 2.0f / width;
            m.matrix[1][1] = 2.0f / height;
            m.matrix[2][2] = 1.0f / (farPlane - nearPlane);
            m.matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
            return m;
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

