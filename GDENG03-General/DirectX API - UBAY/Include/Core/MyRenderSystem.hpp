#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Graphics/MySwapChain.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"

namespace DX3D {
    class MyRenderSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11Device* D3DDevice{ nullptr };
        MyDeviceContext* immediateDeviceContext{ nullptr };
        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
        IDXGIDevice* DXGIDevice{ nullptr };
        IDXGIAdapter* DXGIAdapter{ nullptr };
        IDXGIFactory* DXGIFactory{ nullptr };
        D3D_FEATURE_LEVEL featureLevel{ D3D_FEATURE_LEVEL_11_0 };

        ID3DBlob* temporaryBlob{ nullptr };
        ID3DBlob* vertexShaderBlob{ nullptr };
        ID3DBlob* pixelShaderBlob{ nullptr };
        ID3D11VertexShader* D3DVertexShader{ nullptr };
        ID3D11PixelShader* D3DPixelShader{ nullptr };

        friend class MySwapChain;
        friend class MyVertexBuffer;
        friend class MyConstantBuffer;
        friend class MyIndexBuffer;
        friend class MyVertexShader;
        friend class MyPixelShader;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyRenderSystem();
        ~MyRenderSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Initialize();
        bool Release();
        MySwapChain* CreateSwapChain(HWND windowHandle, UINT width, UINT height);
        MyVertexBuffer* CreateVertexBuffer(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize);
        MyConstantBuffer* CreateConstantBuffer(void* buffer, UINT bufferSize);
        MyIndexBuffer* CreateIndexBuffer(void* indices, UINT indexCount);
        MyVertexShader* CreateVertexShader(const void* shaderByteCode, size_t shaderSize);
        MyPixelShader* CreatePixelShader(const void* shaderByteCode, size_t shaderSize);

        bool CompileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize);
        bool CompilePixelShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize);
        bool ReleaseCompiledShader();
        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyDeviceContext* GetImmedieateDeviceContext() const { return this->immediateDeviceContext; }
    };
} // namespace DX3D

