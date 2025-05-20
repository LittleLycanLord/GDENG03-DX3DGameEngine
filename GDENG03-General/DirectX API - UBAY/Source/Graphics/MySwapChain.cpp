#include "Graphics/MySwapChain.hpp"
#include <iostream>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MySwapChain::MySwapChain() {}
MySwapChain::~MySwapChain() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MySwapChain::Initialize(HWND windowHandle, UINT width, UINT height) {
    ID3D11Device* D3DDevice = MyGraphicsEngine::GetInstance()->D3DDevice;

    DXGI_SWAP_CHAIN_DESC description;
    ZeroMemory(&description, sizeof(description));
    description.BufferCount = 1;
    description.BufferDesc.Width = width;
    description.BufferDesc.Height = height;
    description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    description.BufferDesc.RefreshRate.Numerator = 60;
    description.BufferDesc.RefreshRate.Denominator = 1;
    description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    description.OutputWindow = windowHandle;
    description.SampleDesc.Count = 1;
    description.SampleDesc.Quality = 0;
    description.Windowed = TRUE;

    HRESULT result = MyGraphicsEngine::GetInstance()->DXGIFactory->CreateSwapChain(
        D3DDevice,
        &description,
        &this->DXGISwapChain
    );

    if (FAILED(result))
        return false;


    ID3D11Texture2D* backBuffer = nullptr;
    this->DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    result = D3DDevice->CreateRenderTargetView(
        backBuffer,
        NULL,
        &D3D11RenderTargetView
    );
    backBuffer->Release();

    if (FAILED(result))
        return false;


    return SUCCEEDED(result);
}
bool MySwapChain::Present(bool vsync) {
    if (this->DXGISwapChain)
        this->DXGISwapChain->Present(vsync, 0);
    return true;
}
bool MySwapChain::Release() {
    if (DXGISwapChain) {
        this->DXGISwapChain->Release();
        this->DXGISwapChain = nullptr;
    }
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
