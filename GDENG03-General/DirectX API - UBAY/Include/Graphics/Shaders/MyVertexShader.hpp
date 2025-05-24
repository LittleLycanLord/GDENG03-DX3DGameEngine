#pragma once
#include <d3d11.h>
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"

namespace DX3D {
    class MyVertexShader {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11VertexShader* D3DVertexShader{ nullptr };

        friend class MyGraphicsEngine;
        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVertexShader();
        ~MyVertexShader();

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

