#pragma once
#include <cmath>
#include "Math/MyVector3.hpp"
#include "Math/MyVector4.hpp"
#include "memory"

namespace DX3D {
    class MyMatrix4x4 {
    public:
        float matrix[4][4];

        // Constructors & Destructor
        MyMatrix4x4() { SetIdentity(); }
        ~MyMatrix4x4() {}

        // Assignment & Setters
        void operator=(const MyMatrix4x4& returnMatrix) { memcpy(this->matrix, returnMatrix.matrix, sizeof(float) * 16); }
        void SetMatrix(const MyMatrix4x4& returnMatrix) { memcpy(this->matrix, returnMatrix.matrix, sizeof(float) * 16); }

        // Basic Matrix Operations
        void SetIdentity() {
            memset(this->matrix, 0, sizeof(float) * 16);
            this->matrix[0][0] = 1; this->matrix[1][1] = 1; this->matrix[2][2] = 1; this->matrix[3][3] = 1;
        }
        void Transpose() {
            for (int row = 0; row < 4; ++row)
                for (int col = row + 1; col < 4; ++col)
                    std::swap(this->matrix[row][col], this->matrix[col][row]);
        }
        MyMatrix4x4 operator*(const MyMatrix4x4& rhs) const {
            MyMatrix4x4 result;
            for (int row = 0; row < 4; ++row)
                for (int col = 0; col < 4; ++col) {
                    result.matrix[row][col] = 0.0f;
                    for (int k = 0; k < 4; ++k)
                        result.matrix[row][col] += this->matrix[row][k] * rhs.matrix[k][col];
                }
            return result;
        }
        MyMatrix4x4& operator*=(const MyMatrix4x4& rhs) {
            *this = *this * rhs;
            return *this;
        }

        // Static Constructors
        static MyMatrix4x4 Identity() { MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity(); return returnMatrix; }
        static MyMatrix4x4 Translation(const MyVector3& translation) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix.matrix[3][0] = translation.x; returnMatrix.matrix[3][1] = translation.y; returnMatrix.matrix[3][2] = translation.z;
            return returnMatrix;
        }
        static MyMatrix4x4 Scaling(const MyVector3& sinAngle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix.matrix[0][0] = sinAngle.x; returnMatrix.matrix[1][1] = sinAngle.y; returnMatrix.matrix[2][2] = sinAngle.z;
            return returnMatrix;
        }
        static MyMatrix4x4 RotationX(float angle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            returnMatrix.matrix[1][1] = cosAngle; returnMatrix.matrix[1][2] = sinAngle;
            returnMatrix.matrix[2][1] = -sinAngle; returnMatrix.matrix[2][2] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 RotationY(float angle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            returnMatrix.matrix[0][0] = cosAngle; returnMatrix.matrix[0][2] = -sinAngle;
            returnMatrix.matrix[2][0] = sinAngle; returnMatrix.matrix[2][2] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 RotationZ(float angle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            returnMatrix.matrix[0][0] = cosAngle; returnMatrix.matrix[0][1] = sinAngle;
            returnMatrix.matrix[1][0] = -sinAngle; returnMatrix.matrix[1][1] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 OrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix.matrix[0][0] = 2.0f / width;
            returnMatrix.matrix[1][1] = 2.0f / height;
            returnMatrix.matrix[2][2] = 1.0f / (farPlane - nearPlane);
            returnMatrix.matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
            return returnMatrix;
        }
        static MyMatrix4x4 PerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float yScale = 1.0f / std::tan(fieldOfView / 2.0f);
            float xScale = yScale / aspectRatio;
            returnMatrix.matrix[0][0] = xScale;
            returnMatrix.matrix[1][1] = yScale;
            returnMatrix.matrix[2][2] = farPlane / (farPlane - nearPlane);
            returnMatrix.matrix[2][3] = 1.0f;
            returnMatrix.matrix[3][2] = (-nearPlane * farPlane) / (farPlane - nearPlane);
            return returnMatrix;
        }

        // Transformation Helpers (in-place)
        void Translate(const MyVector3& translation) {
            SetIdentity();
            this->matrix[3][0] = translation.x; this->matrix[3][1] = translation.y; this->matrix[3][2] = translation.z;
        }
        void Scale(const MyVector3& scale) {
            SetIdentity();
            this->matrix[0][0] = scale.x; this->matrix[1][1] = scale.y; this->matrix[2][2] = scale.z;
        }
        void RotateX(float angle) {
            SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            this->matrix[1][1] = cosAngle; this->matrix[1][2] = sinAngle;
            this->matrix[2][1] = -sinAngle; this->matrix[2][2] = cosAngle;
        }
        void RotateY(float angle) {
            SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            this->matrix[0][0] = cosAngle; this->matrix[0][2] = -sinAngle;
            this->matrix[2][0] = sinAngle; this->matrix[2][2] = cosAngle;
        }
        void RotateZ(float angle) {
            SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            this->matrix[0][0] = cosAngle; this->matrix[0][1] = sinAngle;
            this->matrix[1][0] = -sinAngle; this->matrix[1][1] = cosAngle;
        }
        void SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            SetIdentity();
            this->matrix[0][0] = 2.0f / width;
            this->matrix[1][1] = 2.0f / height;
            this->matrix[2][2] = 1.0f / (farPlane - nearPlane);
            this->matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
        }
        void SetPerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
            SetIdentity();
            float yScale = 1.0f / std::tan(fieldOfView / 2.0f);
            float xScale = yScale / aspectRatio;
            this->matrix[0][0] = xScale;
            this->matrix[1][1] = yScale;
            this->matrix[2][2] = farPlane / (farPlane - nearPlane);
            this->matrix[2][3] = 1.0f;
            this->matrix[3][2] = (-nearPlane * farPlane) / (farPlane - nearPlane);
        }

        // Utility Functions
        void SetInverse() { SetMatrix(this->Inverse()); }
        MyMatrix4x4 Inverse() {
            MyMatrix4x4 inverse;
            int a;
            MyVector4 vector, vectors[3];
            float determinant = this->GetDeterminant();
            if (determinant == 0.0f) return inverse; // Return identity if not invertible
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    if (col != row) {
                        a = col;
                        if (col > row) a--;
                        vectors[a].x = this->matrix[col][0];
                        vectors[a].y = this->matrix[col][1];
                        vectors[a].z = this->matrix[col][2];
                        vectors[a].w = this->matrix[col][3];
                    }
                }
                vector.Cross(vectors[0], vectors[1], vectors[2]);
                inverse.matrix[0][row] = (float)pow(-1.0f, row) * vector.x / determinant;
                inverse.matrix[1][row] = (float)pow(-1.0f, row) * vector.y / determinant;
                inverse.matrix[2][row] = (float)pow(-1.0f, row) * vector.z / determinant;
                inverse.matrix[3][row] = (float)pow(-1.0f, row) * vector.w / determinant;
            }
            return inverse;
        }
        float GetDeterminant() {
            MyVector4 minor;
            MyVector4 A = { this->matrix[0][0], this->matrix[0][1], this->matrix[0][2], this->matrix[0][3] };
            MyVector4 B = { this->matrix[1][0], this->matrix[1][1], this->matrix[1][2], this->matrix[1][3] };
            MyVector4 C = { this->matrix[2][0], this->matrix[2][1], this->matrix[2][2], this->matrix[2][3] };
            minor.Cross(A, B, C);
            return -(this->matrix[3][0] * minor.x
                + this->matrix[3][1] * minor.y
                + this->matrix[3][2] * minor.z
                + this->matrix[3][3] * minor.w);
        }
        MyVector3 GetDotProduct(const MyVector3& vector) const {
            float x = vector.x * this->matrix[0][0] + vector.y * this->matrix[1][0] + vector.z * this->matrix[2][0] + this->matrix[3][0];
            float y = vector.x * this->matrix[0][1] + vector.y * this->matrix[1][1] + vector.z * this->matrix[2][1] + this->matrix[3][1];
            float z = vector.x * this->matrix[0][2] + vector.y * this->matrix[1][2] + vector.z * this->matrix[2][2] + this->matrix[3][2];
            return MyVector3(x, y, z);
        }
        MyVector3 GetXDirection() { return MyVector3(this->matrix[0][0], this->matrix[0][1], this->matrix[0][2]); }
        MyVector3 GetYDirection() { return MyVector3(this->matrix[1][0], this->matrix[1][1], this->matrix[1][2]); }
        MyVector3 GetZDirection() { return MyVector3(this->matrix[2][0], this->matrix[2][1], this->matrix[2][2]); }
        MyVector3 GetTranslation() { return MyVector3(this->matrix[3][0], this->matrix[3][1], this->matrix[3][2]); }
    };
} // namespace DX3D

