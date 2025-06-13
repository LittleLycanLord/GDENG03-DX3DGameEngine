#pragma once

#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVector3.hpp"
#include "Core/Input System/MyInputSystem.hpp"
#include "Core/Input System/MyInputListener.hpp"

namespace DX3D {
    class MyCamera : public MyInputListener {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        float windowWidth;
        float windowHeight;
    public:
        MyMatrix4x4 projectionMatrix;
        MyMatrix4x4 viewMatrix;
        MyVector3 cameraPosition;
        MyVector3 rotationInput;
        float deltaTime;
        float moveSpeed = 1.0f;
        float rotationSpeed = 0.1f;

        MyVector3 movementInput;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyCamera(float windowWidth, float WindowHeight);
        ~MyCamera();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Update(float deltaTime);
        void UpdateTransformation();
        void SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane);
        void SetPerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
        //* MyInputListener
        virtual void OnKeyDown(int keyCode) override;
        virtual void OnKeyHold(int keyCode) override;
        virtual void OnKeyUp(int keyCode) override;
        virtual void OnMouseMove(const MyScreenPoint& deltaMousePosition) override;
        virtual void OnLMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnLMBHold(const MyScreenPoint& deltaMousePosition) override;
        virtual void OnLMBUp(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBHold(const MyScreenPoint& deltaMousePosition) override;
        virtual void OnRMBUp(const MyScreenPoint& mousePosition) override;
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

