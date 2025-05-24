#pragma once
#include <d3d11.h>
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"

namespace DX3D {
    class MyPixelShader {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11PixelShader* D3DPixelShader{ nullptr };

        friend class MyGraphicsEngine;
        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyPixelShader();
        ~MyPixelShader();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
        bool Initialize(const void* shaderByteCode, size_t shaderSize);
    public:
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

