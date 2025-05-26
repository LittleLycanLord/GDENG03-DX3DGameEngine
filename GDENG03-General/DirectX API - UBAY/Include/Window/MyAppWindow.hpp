#pragma once
#include <Windows.h>
#include "Window/MyWindow.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/MyVertexBuffer.hpp"
#include "Graphics/MyConstantBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"
#include "Math/MyVec3.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyVertex.hpp"

namespace DX3D {
    class MyAppWindow : public MyWindow {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MySwapChain* swapChain{ nullptr };
        MyVertexBuffer* vertexBuffer{ nullptr };
        MyConstantBuffer* constantBuffer{ nullptr };
        MyVertexShader* vertexShader{ nullptr };
        MyPixelShader* pixelShader{ nullptr };

        unsigned long oldTime = 0;
        float deltaTime = 0;
        float angle = 0;

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

