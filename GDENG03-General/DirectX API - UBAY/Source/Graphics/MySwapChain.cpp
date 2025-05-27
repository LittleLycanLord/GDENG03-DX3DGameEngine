#include "Graphics/MySwapChain.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

extern bool LOG_INFO_SWAPCHAIN;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MySwapChain::MySwapChain() {
    if (LOG_INFO_SWAPCHAIN) std::cout << "[INFO] : MySwapChain constructed" << std::endl;
}
MySwapChain::~MySwapChain() {
    if (LOG_INFO_SWAPCHAIN) std::cout << "[INFO] : MySwapChain destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MySwapChain::Initialize(HWND windowHandle, UINT width, UINT height) {
    if (LOG_INFO_SWAPCHAIN) std::cout << "[INFO] : MySwapChain::Initialize called" << std::endl;

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

    if (!windowHandle) {
        std::cout << "[ERROR] : windowHandle is null in MySwapChain::Initialize" << std::endl;
        return false;
    }
    if (!D3DDevice) {
        std::cout << "[ERROR] : D3DDevice is null in MySwapChain::Initialize" << std::endl;
        return false;
    }
    if (!MyGraphicsEngine::GetInstance()->DXGIFactory) {
        std::cout << "[ERROR] : DXGIFactory is null in MySwapChain::Initialize" << std::endl;
        return false;
    }

    HRESULT result = MyGraphicsEngine::GetInstance()->DXGIFactory->CreateSwapChain(
        D3DDevice,
        &description,
        &this->DXGISwapChain
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateSwapChain failed. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    if (LOG_INFO_SWAPCHAIN)
        std::cout << "[INFO] : SwapChain created successfully" << std::endl;

    ID3D11Texture2D* backBuffer = nullptr;
    HRESULT getBufferResult = this->DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (FAILED(getBufferResult) || !backBuffer) {
        std::cout << "[ERROR] : GetBuffer failed in MySwapChain::Initialize. HRESULT: 0x" << std::hex << getBufferResult << std::endl;
        _com_error err(getBufferResult);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    result = D3DDevice->CreateRenderTargetView(
        backBuffer,
        NULL,
        &D3D11RenderTargetView
    );
    backBuffer->Release();

    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateRenderTargetView failed. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    return SUCCEEDED(result);
}

bool MySwapChain::Present(bool vsync) {
    if (LOG_INFO_SWAPCHAIN) std::cout << "[INFO] : MySwapChain::Present called" << std::endl;

    if (this->DXGISwapChain)
        this->DXGISwapChain->Present(vsync, 0);
    else
        std::cout << "[ERROR] : DXGISwapChain is null in MySwapChain::Present" << std::endl;
    return true;
}

bool MySwapChain::Release() {
    if (LOG_INFO_SWAPCHAIN) std::cout << "[INFO] : MySwapChain::Release called" << std::endl;

    if (DXGISwapChain) {
        this->DXGISwapChain->Release();
        this->DXGISwapChain = nullptr;
    }
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
