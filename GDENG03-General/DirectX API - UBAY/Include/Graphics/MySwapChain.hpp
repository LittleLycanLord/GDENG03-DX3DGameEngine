#pragma once
#include <d3d11.h>
#include <Windows.h>
#include "Graphics/MyGraphicsEngine.hpp"

namespace DX3D {
    class MySwapChain {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        IDXGISwapChain* DXGISwapChain{ nullptr };
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

