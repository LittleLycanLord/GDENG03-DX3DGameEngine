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
        void RotateX(float angle) {
            float cosAngle = (float)cos(angle);
            float sinAngle = (float)sin(angle);
            matrix[1][1] = cosAngle;
            matrix[1][2] = sinAngle;
            matrix[2][1] = -sinAngle;
            matrix[2][2] = cosAngle;
        }
        void RotateY(float angle) {
            float cosAngle = (float)cos(angle);
            float sinAngle = (float)sin(angle);
            matrix[0][0] = cosAngle;
            matrix[0][2] = -sinAngle;
            matrix[2][0] = sinAngle;
            matrix[2][2] = cosAngle;
        }
        void RotateZ(float angle) {
            float cosAngle = (float)cos(angle);
            float sinAngle = (float)sin(angle);
            matrix[0][0] = cosAngle;
            matrix[0][1] = sinAngle;
            matrix[1][0] = -sinAngle;
            matrix[1][1] = cosAngle;
        }

        void SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            this->SetIdentity();
            matrix[0][0] = 2.0f / width;
            matrix[1][1] = 2.0f / height;
            matrix[2][2] = 1.0f / (farPlane - nearPlane);
            matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
        }

        // Matrix multiplication
        MyMatrix4x4 operator *(const MyMatrix4x4& rightHandSide) const {
            MyMatrix4x4 result;
            for (int row = 0; row < 4; ++row)
                for (int column = 0; column < 4; ++column) {
                    result.matrix[row][column] = 0.0f;
                    for (int k = 0; k < 4; ++k)
                        result.matrix[row][column] += this->matrix[row][k] * rightHandSide.matrix[k][column];
                }
            return result;
        }

        MyMatrix4x4& operator*=(const MyMatrix4x4& rightHandSide) {
            *this = *this * rightHandSide;
            return *this;
        }

        MyVec3 DotProduct(const MyVec3& multipliedVector) const {
            float x = multipliedVector.x * matrix[0][0] + multipliedVector.y * matrix[1][0] + multipliedVector.z * matrix[2][0] + matrix[3][0];
            float y = multipliedVector.x * matrix[0][1] + multipliedVector.y * matrix[1][1] + multipliedVector.z * matrix[2][1] + matrix[3][1];
            float z = multipliedVector.x * matrix[0][2] + multipliedVector.y * matrix[1][2] + multipliedVector.z * matrix[2][2] + matrix[3][2];
            return MyVec3(x, y, z);
        }
        void Transpose() {
            for (int row = 0; row < 4; ++row)
                for (int column = row + 1; column < 4; ++column)
                    std::swap(matrix[row][column], matrix[column][row]);
        }

        static MyMatrix4x4 Identity() {
            MyMatrix4x4 returnMatrix;
            returnMatrix.SetIdentity();
            return returnMatrix;
        }
        static MyMatrix4x4 Translation(const MyVec3& translation) {
            MyMatrix4x4 returnMatrix;
            returnMatrix.SetIdentity();
            returnMatrix.matrix[3][0] = translation.x;
            returnMatrix.matrix[3][1] = translation.y;
            returnMatrix.matrix[3][2] = translation.z;
            return returnMatrix;
        }
        static MyMatrix4x4 Scaling(const MyVec3& scale) {
            MyMatrix4x4 returnMatrix;
            returnMatrix.SetIdentity();
            returnMatrix.matrix[0][0] = scale.x;
            returnMatrix.matrix[1][1] = scale.y;
            returnMatrix.matrix[2][2] = scale.z;
            return returnMatrix;
        }
        static MyMatrix4x4 RotationX(float angle) {
            MyMatrix4x4 returnMatrix;
            float cosAngle = (float)cos(angle);
            float sinAngle = (float)sin(angle);
            returnMatrix.matrix[1][1] = cosAngle;
            returnMatrix.matrix[1][2] = sinAngle;
            returnMatrix.matrix[2][1] = -sinAngle;
            returnMatrix.matrix[2][2] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 RotationY(float angle) {
            MyMatrix4x4 returnMatrix;
            float cosAngle = (float)cos(angle);
            float sinAngle = (float)sin(angle);
            returnMatrix.matrix[0][0] = cosAngle;
            returnMatrix.matrix[0][2] = -sinAngle;
            returnMatrix.matrix[2][0] = sinAngle;
            returnMatrix.matrix[2][2] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 RotationZ(float angle) {
            MyMatrix4x4 returnMatrix;
            float cosAngle = (float)cos(angle);
            float sinAngle = (float)sin(angle);
            returnMatrix.matrix[0][0] = cosAngle;
            returnMatrix.matrix[0][1] = sinAngle;
            returnMatrix.matrix[1][0] = -sinAngle;
            returnMatrix.matrix[1][1] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 OrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            MyMatrix4x4 returnMatrix;
            returnMatrix.SetIdentity();
            returnMatrix.matrix[0][0] = 2.0f / width;
            returnMatrix.matrix[1][1] = 2.0f / height;
            returnMatrix.matrix[2][2] = 1.0f / (farPlane - nearPlane);
            returnMatrix.matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
            return returnMatrix;
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

