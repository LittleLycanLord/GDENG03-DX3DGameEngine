#pragma once
#include <Windows.h>
#include <vector>
#include <exception>
#include "Window/MyWindow.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVec3.hpp"
#include "Math/MyVec2.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyVertex.hpp"
#include "Core/Primitives/MyTriangle.hpp"
#include "Core/Primitives/MyQuad.hpp"
#include "Core/Input System/MyInputSystem.hpp"
#include "Core/Input System/MyInputListener.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"

namespace DX3D {
    class MyAppWindow : public MyWindow, public MyInputListener {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MySwapChain* swapChain{ nullptr };
        MyVertexBuffer* vertexBuffer{ nullptr };
        MyConstantBuffer* constantBuffer{ nullptr };
        MyIndexBuffer* indexBuffer{ nullptr };
        MyVertexShader* vertexShader{ nullptr };
        MyPixelShader* pixelShader{ nullptr };

        ULONGLONG oldTime = 0;
        ULONGLONG newTime = 0;
        float deltaTime = 0;

        bool lockMouse = true;

        //* Experimental variables
        float experimentalDelta = 0;
        float rotationSpeed = 0.1f;
        float xRotation = 0.0f;
        float yRotation = 0.0f;

        float moveSpeed = 1.0f;

        MyConstant constantData;
        MyMatrix4x4 cameraMatrix;
        MyVec3 cameraMoveInput;
        MyVec3 cameraPosition;
        MyVec3 cameraRotation;


        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyAppWindow();
        ~MyAppWindow();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
        void UpdateDeltaTime();
        void UpdateObjects();
    public:

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        //* MyWindow
        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnDestroy() override;
        virtual void OnSetFocus() override;
        virtual void OnKillFocus() override;

        //* MyInputListener
        virtual void OnKeyDown(int keyCode) override;
        virtual void OnKeyHold(int keyCode) override;
        virtual void OnKeyUp(int keyCode) override;
        virtual void OnMouseMove(const MyScreenPoint& deltaMousePosition) override;
        virtual void OnLMBUp(const MyScreenPoint& mousePosition) override;
        virtual void OnLMBHold(const MyScreenPoint& deltaMousePosition) override;
        virtual void OnLMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBUp(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBHold(const MyScreenPoint& deltaMousePosition) override;
        virtual void OnRMBDown(const MyScreenPoint& mousePosition) override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

