#pragma once
#include <Window/MyWindow.hpp>
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/MyVertexBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"
#include "Math/MyVec3.hpp"
#include "Math/MyVertex.hpp"

namespace DX3D {
    class MyAppWindow : public MyWindow {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MySwapChain* swapChain{ nullptr };
        MyVertexBuffer* vertexBuffer{ nullptr };
        MyVertexShader* vertexShader{ nullptr };
        MyPixelShader* pixelShader{ nullptr }; // Add this line

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

