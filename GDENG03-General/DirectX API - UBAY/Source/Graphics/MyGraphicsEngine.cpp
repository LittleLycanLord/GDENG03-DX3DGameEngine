#include "Graphics/MyGraphicsEngine.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyGraphicsEngine::MyGraphicsEngine() {}
MyGraphicsEngine::~MyGraphicsEngine() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyGraphicsEngine::Initialize() {
    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

    HRESULT result = 0;
    for (UINT driverTypeIndex = 0; driverTypeIndex < ARRAYSIZE(driverTypes); ) {
        result = D3D11CreateDevice(
            NULL,
            driverTypes[driverTypeIndex],
            NULL,
            NULL,
            featureLevels,
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,
            &this->D3DDevice,
            &this->featureLevel,
            &this->D3DDeviceContext
        );
        if (SUCCEEDED(result))
            break;

        driverTypeIndex++;
    }

    immediateDeviceContext = new MyDeviceContext(this->D3DDeviceContext);

    this->D3DDevice->QueryInterface(
        __uuidof(IDXGIDevice),
        (void**)&this->DXGIDevice
    );
    this->DXGIDevice->GetParent(
        __uuidof(IDXGIAdapter),
        (void**)&this->DXGIAdapter
    );
    this->DXGIAdapter->GetParent(
        __uuidof(IDXGIFactory),
        (void**)&this->DXGIFactory
    );

    return SUCCEEDED(result);
}
bool MyGraphicsEngine::Release() {
    this->DXGIDevice->Release();
    this->DXGIAdapter->Release();
    this->DXGIFactory->Release();
    this->D3DDevice->Release();
    this->D3DDeviceContext->Release();
    return true;
}
MySwapChain* MyGraphicsEngine::CreateSwapChain() {
    MySwapChain* swapChain = new MySwapChain();
    return swapChain;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝