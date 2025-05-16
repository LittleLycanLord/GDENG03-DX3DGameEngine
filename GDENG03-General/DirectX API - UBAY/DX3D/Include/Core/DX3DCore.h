#pragma once
#include <stdexcept>
#include <memory>

namespace DX3D {
    //* ╔══════════════════════╗
    //* ║ Forward Declarations ║
    //* ╚══════════════════════╝
    class MyBase;
    class MyWindow;
    class MyGame;
    class MyGraphicsEngine;
    class MyGraphicsDevice;
    class MyLogger;
    class MySwapChain;
    class MyVertexBuffer;
    class MyDisplay;
    class MyDeviceContext;

    using SwapChainPointer = std::shared_ptr<MySwapChain>;
    using DeviceContextPointer = std::shared_ptr<MyDeviceContext>;
}