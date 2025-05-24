#include "Graphics/MyGraphicsEngine.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

extern bool LOG_INFO_GRAPHICS_ENGINE;
extern bool LOG_INFO_SHADER;

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
            D3D11_CREATE_DEVICE_DEBUG,
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

    if (FAILED(result)) {
        std::cout << "[ERROR] : D3D11CreateDevice failed in MyGraphicsEngine::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    if (LOG_INFO_GRAPHICS_ENGINE)
        std::cout << "[INFO] : D3D11 Device created successfully" << std::endl;

    immediateDeviceContext = new MyDeviceContext(this->D3DDeviceContext);

    HRESULT hr = this->D3DDevice->QueryInterface(
        __uuidof(IDXGIDevice),
        (void**)&this->DXGIDevice
    );
    if (FAILED(hr)) {
        std::cout << "[ERROR] : QueryInterface for IDXGIDevice failed in MyGraphicsEngine::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }
    hr = this->DXGIDevice->GetParent(
        __uuidof(IDXGIAdapter),
        (void**)&this->DXGIAdapter
    );
    if (FAILED(hr)) {
        std::cout << "[ERROR] : GetParent for IDXGIAdapter failed in MyGraphicsEngine::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }
    hr = this->DXGIAdapter->GetParent(
        __uuidof(IDXGIFactory),
        (void**)&this->DXGIFactory
    );
    if (FAILED(hr)) {
        std::cout << "[ERROR] : GetParent for IDXGIFactory failed in MyGraphicsEngine::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    return SUCCEEDED(result);
}

bool MyGraphicsEngine::Release() {
    if (this->DXGIDevice) this->DXGIDevice->Release();
    else std::cout << "[ERROR] : DXGIDevice is already null in MyGraphicsEngine::Release" << std::endl;
    if (this->DXGIAdapter) this->DXGIAdapter->Release();
    else std::cout << "[ERROR] : DXGIAdapter is already null in MyGraphicsEngine::Release" << std::endl;
    if (this->DXGIFactory) this->DXGIFactory->Release();
    else std::cout << "[ERROR] : DXGIFactory is already null in MyGraphicsEngine::Release" << std::endl;
    if (this->D3DDevice) this->D3DDevice->Release();
    else std::cout << "[ERROR] : D3DDevice is already null in MyGraphicsEngine::Release" << std::endl;
    if (this->D3DDeviceContext) this->D3DDeviceContext->Release();
    else std::cout << "[ERROR] : D3DDeviceContext is already null in MyGraphicsEngine::Release" << std::endl;
    return true;
}

MySwapChain* MyGraphicsEngine::CreateSwapChain() {
    MySwapChain* swapChain = new MySwapChain();
    if (!swapChain) {
        std::cout << "[ERROR] : Failed to allocate MySwapChain in MyGraphicsEngine::CreateSwapChain" << std::endl;
    }
    return swapChain;
}

MyVertexBuffer* MyGraphicsEngine::CreateVertexBuffer() {
    MyVertexBuffer* vb = new MyVertexBuffer();
    if (!vb) {
        std::cout << "[ERROR] : Failed to allocate MyVertexBuffer in MyGraphicsEngine::CreateVertexBuffer" << std::endl;
    }
    return vb;
}

bool MyGraphicsEngine::SetShaders() {
    if (!D3DVertexShader || !D3DPixelShader) {
        std::cout << "[ERROR] : D3DVertexShader or D3DPixelShader is null in MyGraphicsEngine::SetShaders" << std::endl;
        return false;
    }
    immediateDeviceContext->D3DDeviceContext->VSSetShader(D3DVertexShader, nullptr, 0);
    immediateDeviceContext->D3DDeviceContext->PSSetShader(D3DPixelShader, nullptr, 0);
    return true;
}

MyVertexShader* MyGraphicsEngine::CreateVertexShader(const void* shaderByteCode, size_t shaderSize) {
    MyVertexShader* vertexShader = new MyVertexShader();
    if (!vertexShader) {
        std::cout << "[ERROR] : Failed to allocate MyVertexShader in MyGraphicsEngine::CreateVertexShader" << std::endl;
        return nullptr;
    }
    if (!vertexShader->Initialize(shaderByteCode, shaderSize)) {
        vertexShader->Release();
        delete vertexShader;
        std::cout << "[ERROR] : VertexShader initialization failed in MyGraphicsEngine::CreateVertexShader" << std::endl;
        return nullptr;
    }
    return vertexShader;
}

MyPixelShader* MyGraphicsEngine::CreatePixelShader(const void* shaderByteCode, size_t shaderSize) {
    MyPixelShader* pixelShader = new MyPixelShader();
    if (!pixelShader) {
        std::cout << "[ERROR] : Failed to allocate MyPixelShader in MyGraphicsEngine::CreatePixelShader" << std::endl;
        return nullptr;
    }
    if (!pixelShader->Initialize(shaderByteCode, shaderSize)) {
        pixelShader->Release();
        delete pixelShader;
        std::cout << "[ERROR] : PixelShader initialization failed in MyGraphicsEngine::CreatePixelShader" << std::endl;
        return nullptr;
    }
    return pixelShader;
}

bool MyGraphicsEngine::CompileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
    ID3DBlob* errorBlob = nullptr;

    HRESULT result = D3DCompileFromFile(
        fileName,
        nullptr,
        nullptr,
        entryPoint,
        "vs_5_0",
        0,
        0,
        &this->temporaryBlob,
        &errorBlob
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : D3DCompileFromFile failed in MyGraphicsEngine::CompileVertexShader. HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "[ERROR] : " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_SHADER)
        std::wcout << L"[INFO] : Vertex shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyGraphicsEngine::CompilePixelShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
    ID3DBlob* errorBlob = nullptr;

    HRESULT result = D3DCompileFromFile(
        fileName,
        nullptr,
        nullptr,
        entryPoint,
        "ps_5_0",
        0,
        0,
        &this->temporaryBlob,
        &errorBlob
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : D3DCompileFromFile failed in MyGraphicsEngine::CompilePixelShader. HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "[ERROR] : " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_SHADER)
        std::wcout << L"[INFO] : Pixel shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyGraphicsEngine::ReleaseCompiledShader() {
    if (this->temporaryBlob) {
        this->temporaryBlob->Release();
        this->temporaryBlob = nullptr;
    }
    return true;
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝