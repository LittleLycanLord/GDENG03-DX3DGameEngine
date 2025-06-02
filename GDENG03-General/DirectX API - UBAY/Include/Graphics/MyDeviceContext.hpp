#pragma once
#include <d3d11.h>
#include "Math/MyVec4.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"

namespace DX3D {
    class MySwapChain;
    class MyVertexBuffer;
    class MyIndexBuffer;
    class MyVertexShader;
    class MyPixelShader; // Forward declaration of MyPixelShader
    class MyDeviceContext {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
        friend class MyGraphicsEngine;
        friend class MyConstantBuffer;
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
        bool ClearRenderTargetColor(MySwapChain* swapChain, MyVec4 color);
        void SetVertexBuffer(MyVertexBuffer* vertexBuffer);
        void SetIndexBuffer(MyIndexBuffer* indexBuffer);
        void SetViewPortSize(UINT width, UINT height);
        void SetVertexShader(MyVertexShader* vertexShader);
        void SetPixelShader(MyPixelShader* pixelShader);
        void SetConstantBuffer(MyVertexShader* vertexShader, MyConstantBuffer* constantBuffer);
        void SetConstantBuffer(MyPixelShader* pixelShader, MyConstantBuffer* constantBuffer);

        void DrawTriangles(UINT vertexCount, UINT startVertexIndex);
        void DrawIndexedTriangles(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation) ;
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

