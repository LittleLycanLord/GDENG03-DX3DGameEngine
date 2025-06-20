#pragma once
#include <Windows.h>
#include <vector>
#include "Window/MyWindow.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVec3.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyVertex.hpp"
#include "Core/Primitives/MyTriangle.hpp"
#include "Core/Primitives/MyCircle.hpp"
#include "Core/Primitives/MyQuad.hpp"
#include "Game/Input System/MyInputSystem.hpp"
#include "Game/Input System/MyInputListener.hpp"
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

        unsigned long oldTime = 0;
        unsigned long newTime = 0;
        float deltaTime = 0;

        //* Experimental variables
        float experimentalDelta = 0;
        float rotationSpeed = 1.0f; // Speed of rotation in radians per frame
        float xRotation = 0.0f;
        float yRotation = 0.0f;

        //* Bouncing Circles
        std::vector<MyCircle*> circles;
        MyCircle* mostRecentCircle;

        MyConstant constantData;

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
        void SpawnCircle();
        void DeleteMostRecentCircle();
        void DeleteAllCircles();

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        //* MyWindow
        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnDestroy() override;
        //* MyInputListener
        virtual void OnKeyDown(int keyCode) override;
        virtual void OnKeyHold(int keyCode) override;
        virtual void OnKeyUp(int keyCode) override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

