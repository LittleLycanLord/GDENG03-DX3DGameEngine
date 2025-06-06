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
        bool ClearRenderTargetColor(MySwapChainPtr swapChain, MyVec4 color);
        void SetVertexBuffer(MyVertexBufferPtr vertexBuffer);
        void SetIndexBuffer(MyIndexBufferPtr indexBuffer);
        void SetViewPortSize(UINT width, UINT height);
        void SetVertexShader(MyVertexShaderPtr vertexShader);
        void SetPixelShader(MyPixelShaderPtr pixelShader);
        void SetConstantBuffer(MyVertexShaderPtr vertexShader, MyConstantBufferPtr constantBuffer);
        void SetConstantBuffer(MyPixelShaderPtr pixelShader, MyConstantBufferPtr constantBuffer);

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

