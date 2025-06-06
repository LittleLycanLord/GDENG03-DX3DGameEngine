#pragma once
#include <d3d11.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Math/MyVec4.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"

namespace DX3D {
    class MyDeviceContext {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem { nullptr };
        
        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
        
        friend class MyRenderSystem;
        friend class MyConstantBuffer;
    public:
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyDeviceContext(ID3D11DeviceContext* D3DDeviceContex, MyRenderSystem* renderSystem);
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

