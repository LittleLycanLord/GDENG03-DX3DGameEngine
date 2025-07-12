#pragma once
#include <Windows.h>
#include <vector>
#include <exception>
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "Window/MyWindow.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVector3.hpp"
#include "Math/MyVector2.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyVertex.hpp"
#include "Game/MyCamera.hpp"
#include "Core/Primitives/MyTriangle.hpp"
#include "Core/Primitives/MyQuad.hpp"
#include "Core/Input System/MyInputSystem.hpp"
#include "Core/Input System/MyInputListener.hpp"
#include "Core/Resource System/Managers/MyTextureManager.hpp"
#include "Core/Resource System/Managers/MyMeshManager.hpp"
#include "Core/Resource System/Managers/MyTexture.hpp"
#include "Core/Resource System/Managers/MyMesh.hpp"
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
        MySwapChainPtr swapChain{ nullptr };
        MyVertexBufferPtr vertexBuffer{ nullptr };
        MyConstant globalConstantData;
        MyConstantBufferPtr globalConstantBuffer{ nullptr };
        MyIndexBufferPtr indexBuffer{ nullptr };
        MyHullShaderPtr hullShader{ nullptr };
        MyDomainShaderPtr domainShader{ nullptr };
        MyVertexShaderPtr vertexShader{ nullptr };
        MyPixelShaderPtr pixelShader{ nullptr };

        bool freeMouse{ false };
        MyCameraPtr activeCamera{ nullptr };
        std::vector<MyCameraPtr> cameras;
        std::vector<MyMeshPtr> meshes;

        ULONGLONG oldTime = 0;
        ULONGLONG newTime = 0;
        float deltaTime = 0;


        //* Experimental variables
        float experimentalDelta = 0;

        MyTexturePtr sampleTexture{ nullptr };
        MyMeshPtr sampleMesh{ nullptr };

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
        //* Initialization
        void InitializeShaders();
        void InitializeConstantData();
        void DebugLaunchFunction();

        //* Runtime
        void ImGuiUpdate();

        void UpdateDeltaTime();
        void UpdateObjects();
        void UpdateConstantBuffer();
        void UpdateShaders();
        void DrawLoop();
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
        virtual void OnMouseMove(const MyVector2& deltaMousePosition) override;
        virtual void OnLMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnLMBHold(const MyVector2& deltaMousePosition) override;
        virtual void OnLMBUp(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBHold(const MyVector2& deltaMousePosition) override;
        virtual void OnRMBUp(const MyScreenPoint& mousePosition) override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

