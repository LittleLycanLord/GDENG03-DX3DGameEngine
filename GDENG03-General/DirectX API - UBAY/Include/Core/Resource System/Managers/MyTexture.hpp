#pragma once
#include <string>
#include <iostream>
#include <comdef.h>
#include <exception>
#include <d3d11.h>
#include <DirectXTex.h>
#include "Core/Prerequisites.hpp"
#include "Core/Resource System/MyResource.hpp"
#include "Graphics/MyGraphicsEngine.hpp"

namespace DX3D {
    class MyTexture : public MyResource {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11Resource* D3DTexture{ nullptr };
        ID3D11ShaderResourceView* D3DShaderResourceView{ nullptr };

        friend class MyDeviceContext;
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyTexture(const wchar_t* resourcePath);
        ~MyTexture();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:

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

