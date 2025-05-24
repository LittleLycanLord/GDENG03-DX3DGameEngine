#pragma once
#include "Graphics/MyDeviceContext.hpp"

namespace DX3D {
    class MyVertexBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        UINT vertexSize;
        UINT vertexCount;
        ID3D11Buffer* vertexBuffer{ nullptr };
        ID3D11InputLayout* inputLayout{ nullptr };

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

