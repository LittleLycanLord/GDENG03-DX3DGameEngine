#pragma once
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include <iostream>
#include <comdef.h>

namespace DX3D {
    class MyVertexBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        UINT vertexSize{ 0 };
        UINT vertexCount{ 0 };
        ID3D11Buffer* D3DVertexBuffer{ nullptr };
        ID3D11InputLayout* D3DInputLayout{ nullptr };

        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVertexBuffer();
        ~MyVertexBuffer();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Load(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize);
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
        UINT GetVertexCount() const { return vertexCount; }
        UINT GetVertexSize() const { return vertexSize; }
    };
} // namespace DX3D

