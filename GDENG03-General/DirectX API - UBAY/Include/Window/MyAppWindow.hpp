#pragma once
#include <Windows.h>
#include <vector>
#include "Window/MyWindow.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVec3.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyVertex.hpp"
#include "Core/Primitives/MyTriangle.hpp"
#include "Core/Primitives/MyQuad.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"

namespace DX3D {
    class MyAppWindow : public MyWindow {
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
        float experimentalDelta = 0;

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

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnDestroy() override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

