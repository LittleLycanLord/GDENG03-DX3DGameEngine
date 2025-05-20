#pragma once
#include <d3d11.h>
#include <Windows.h>
#include "Graphics/MyGraphicsEngine.hpp"

namespace DX3D {
    class MyDeviceContext;
    class MySwapChain {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        IDXGISwapChain* DXGISwapChain;
        ID3D11RenderTargetView* D3D11RenderTargetView{ nullptr };
        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MySwapChain();
        ~MySwapChain();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Initialize(HWND windowHandle, UINT width, UINT height);
        bool Present(bool vsync);
        bool Release();


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

