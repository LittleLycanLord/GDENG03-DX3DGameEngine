#pragma once
#include <d3d11.h>
#include "Graphics/MySwapChain.hpp"

namespace DX3D {
    //* ╔══════════════════════╗
    //* ║ Forward Declarations ║
    //* ╚══════════════════════╝

    class MyGraphicsEngine {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11Device* D3DDevice{ nullptr };
        IDXGIDevice* DXGIDevice{ nullptr };
        IDXGIAdapter* DXGIAdapter{ nullptr };
        IDXGIFactory* DXGIFactory{ nullptr };
        D3D_FEATURE_LEVEL featureLevel{ D3D_FEATURE_LEVEL_11_0 };
        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
        friend class MySwapChain;
    public:
        static MyGraphicsEngine* GetInstance() {
            static MyGraphicsEngine graphicsEngine;
            return &graphicsEngine;
        }

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyGraphicsEngine();
        ~MyGraphicsEngine();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Initialize();
        bool Release();
        MySwapChain* CreateSwapChain(HWND windowHandle, UINT width, UINT height);
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

