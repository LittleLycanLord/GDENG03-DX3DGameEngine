#pragma once
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include <iostream>
#include <comdef.h>

namespace DX3D {
    class MyIndexBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        UINT indexCount{ 0 };
        ID3D11Buffer* D3DIndexBuffer{ nullptr };

        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyIndexBuffer();
        ~MyIndexBuffer();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Load(void* indices, UINT indexCount);
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
        UINT GetIndexCount() const { return indexCount; }
    };
} // namespace DX3D

