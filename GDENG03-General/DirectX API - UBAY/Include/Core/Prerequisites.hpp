#pragma once
#include <memory>

namespace DX3D {
    class MySwapChain;
    class MyDeviceContext;
    class MyVertexBuffer;
    class MyConstantBuffer;
    class MyIndexBuffer;
    class MyVertexShader;
    class MyPixelShader;
    class MyRenderSystem;
    class MyGraphicsEngine;

    typedef std::shared_ptr<MySwapChain> MySwapChainPtr;
    typedef std::shared_ptr<MyDeviceContext> MyDeviceContextPtr;
    typedef std::shared_ptr<MyVertexBuffer> MyVertexBufferPtr;
    typedef std::shared_ptr<MyConstantBuffer> MyConstantBufferPtr;
    typedef std::shared_ptr<MyIndexBuffer> MyIndexBufferPtr;
    typedef std::shared_ptr<MyVertexShader> MyVertexShaderPtr;
    typedef std::shared_ptr<MyPixelShader> MyPixelShaderPtr;
} // namespace DX3D

