#pragma once
#include <d3d11.h>
#include "Math/Vec4.hpp"

namespace DX3D {
    class MySwapChain;
    class MyDeviceContext {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyDeviceContext(ID3D11DeviceContext* D3DDeviceContext);
        ~MyDeviceContext();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool ClearRenderTargetColor(MySwapChain* swapChain, Vec4 color);
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

