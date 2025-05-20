#include "Graphics/MyGraphicsEngine.hpp"
//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyGraphicsEngine::MyGraphicsEngine() {}
DX3D::MyGraphicsEngine::~MyGraphicsEngine() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool DX3D::MyGraphicsEngine::Initialize() {
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
    return SUCCEEDED(result);
}
bool DX3D::MyGraphicsEngine::Release() {
    this->D3DDevice->Release();
    this->D3DDeviceContext->Release();
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝