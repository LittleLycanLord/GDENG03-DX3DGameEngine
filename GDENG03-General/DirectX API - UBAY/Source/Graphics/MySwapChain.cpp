#include "Graphics/MySwapChain.hpp"
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
    ID3D11Device* device = MyGraphicsEngine::GetInstance()->D3DDevice;
    DXGI_SWAP_CHAIN_DESC description;
    ZeroMemory(&description, sizeof(DXGI_SWAP_CHAIN_DESC));
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
        MyGraphicsEngine::GetInstance()->D3DDevice,
        &description,
        &this->DXGISwapChain
    );
    return SUCCEEDED(result);
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
