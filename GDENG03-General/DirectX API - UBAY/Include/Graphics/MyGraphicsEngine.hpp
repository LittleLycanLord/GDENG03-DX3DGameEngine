#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Graphics/MySwapChain.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MyVertexBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"

namespace DX3D {
    class MyGraphicsEngine {
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
        friend class MyVertexShader;
        friend class MyPixelShader;
    public:
        static MyGraphicsEngine* GetInstance() {
            static MyGraphicsEngine graphicsEngine;
            return &graphicsEngine;
        }

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyGraphicsEngine();
        ~MyGraphicsEngine();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Initialize();
        bool Release();
        MySwapChain* CreateSwapChain();
        MyVertexBuffer* CreateVertexBuffer();
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

