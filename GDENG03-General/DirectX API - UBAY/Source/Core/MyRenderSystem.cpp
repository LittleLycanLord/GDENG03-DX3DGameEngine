#include "Core/MyRenderSystem.hpp"

using namespace DX3D;

extern bool LOG_INFO_RENDER_SYSTEM;
extern bool LOG_INFO_VERTEX_SHADER;
extern bool LOG_INFO_PIXEL_SHADER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyRenderSystem::MyRenderSystem() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyRenderSystem constructed" << std::endl;


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
        std::cout << "D3D11CreateDevice failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return;
    }

    if (LOG_INFO_RENDER_SYSTEM)
        std::cout << "[INFO] : D3D11 Device created successfully" << std::endl;

    immediateDeviceContext = std::make_shared<MyDeviceContext>(this->D3DDeviceContext, this);

    HRESULT hr = this->D3DDevice->QueryInterface(
        __uuidof(IDXGIDevice),
        (void**)&this->DXGIDevice
    );
    if (FAILED(hr)) {
        std::cout << "QueryInterface for IDXGIDevice failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return;
    }
    hr = this->DXGIDevice->GetParent(
        __uuidof(IDXGIAdapter),
        (void**)&this->DXGIAdapter
    );
    if (FAILED(hr)) {
        std::cout << "GetParent for IDXGIAdapter failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return;
    }
    hr = this->DXGIAdapter->GetParent(
        __uuidof(IDXGIFactory),
        (void**)&this->DXGIFactory
    );
    if (FAILED(hr)) {
        std::cout << "GetParent for IDXGIFactory failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return;
    }

}
MyRenderSystem::~MyRenderSystem() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyRenderSystem destructed" << std::endl;

    if (this->DXGIDevice) {
        this->DXGIDevice->Release();
        this->DXGIDevice = nullptr;
    }
    if (this->DXGIAdapter) {
        this->DXGIAdapter->Release();
        this->DXGIAdapter = nullptr;
    }
    if (this->DXGIFactory) {
        this->DXGIFactory->Release();
        this->DXGIFactory = nullptr;
    }
    if (this->D3DDevice) {
        this->D3DDevice->Release();
        this->D3DDevice = nullptr;
    }

    this->immediateDeviceContext = nullptr;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
MySwapChainPtr MyRenderSystem::CreateSwapChain(HWND windowHandle, UINT width, UINT height) {
    try {
        MySwapChainPtr swapChain = std::make_shared<MySwapChain>(windowHandle, width, height, this);
        if (!swapChain) {
            std::cerr << "[ERROR] Failed to allocate MySwapChain in MyRenderSystem::CreateSwapChain" << std::endl;
            throw std::exception("Failed to allocate MySwapChain in MyRenderSystem::CreateSwapChain");
        }
        return swapChain;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in CreateSwapChain: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyVertexBufferPtr MyRenderSystem::CreateVertexBuffer(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize) {
    try {
        MyVertexBufferPtr vertexBuffer = std::make_shared<MyVertexBuffer>(vertexList, vertexSize, vertexCount, shaderByteCode, shaderByteCodeSize, this);
        if (!vertexBuffer) {
            std::cerr << "[ERROR] Failed to allocate MyVertexBuffer in MyRenderSystem::CreateVertexBuffer" << std::endl;
            throw std::exception("Failed to allocate MyVertexBuffer in MyRenderSystem::CreateVertexBuffer");
        }
        return vertexBuffer;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in CreateVertexBuffer: " << ex.what() << std::endl;
        return nullptr;
    }
}
MyConstantBufferPtr MyRenderSystem::CreateConstantBuffer(void* buffer, UINT bufferSize) {
    try {
        MyConstantBufferPtr constantBuffer = std::make_shared<MyConstantBuffer>(buffer, bufferSize, this);
        if (!constantBuffer) {
            std::cerr << "[ERROR] Failed to allocate MyConstantBuffer in MyRenderSystem::CreateConstantBuffer" << std::endl;
            throw std::exception("Failed to allocate MyConstantBuffer in MyRenderSystem::CreateConstantBuffer");
        }
        return constantBuffer;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in CreateConstantBuffer: " << ex.what() << std::endl;
        return nullptr;
    }
}
MyIndexBufferPtr MyRenderSystem::CreateIndexBuffer(void* indices, UINT indexCount) {
    try {
        MyIndexBufferPtr indexBuffer = std::make_shared<MyIndexBuffer>(indices, indexCount, this);
        if (!indexBuffer) {
            std::cerr << "[ERROR] Failed to allocate MyIndexBuffer in MyRenderSystem::CreateIndexBuffer" << std::endl;
            throw std::exception("Failed to allocate MyIndexBuffer in MyRenderSystem::CreateIndexBuffer");
        }
        return indexBuffer;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in CreateIndexBuffer: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyVertexShaderPtr MyRenderSystem::CreateVertexShader(const void* shaderByteCode, size_t shaderSize) {
    try {
        MyVertexShaderPtr vertexShader = std::make_shared<MyVertexShader>(shaderByteCode, shaderSize, this);
        if (!vertexShader) {
            std::cerr << "[ERROR] Failed to allocate MyVertexShader in MyRenderSystem::CreateVertexShader" << std::endl;
            throw std::exception("Failed to allocate MyVertexShader in MyRenderSystem::CreateVertexShader");
        }
        return vertexShader;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in CreateVertexShader: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyPixelShaderPtr MyRenderSystem::CreatePixelShader(const void* shaderByteCode, size_t shaderSize) {
    try {
        MyPixelShaderPtr pixelShader = std::make_shared<MyPixelShader>(shaderByteCode, shaderSize, this);
        if (!pixelShader) {
            std::cerr << "[ERROR] Failed to allocate MyPixelShader in MyRenderSystem::CreatePixelShader" << std::endl;
            throw std::exception("Failed to allocate MyPixelShader in MyRenderSystem::CreatePixelShader");
        }
        return pixelShader;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in CreatePixelShader: " << ex.what() << std::endl;
        return nullptr;
    }
}

bool MyRenderSystem::CompileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
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
        std::cout << "D3DCompileFromFile failed in MyRenderSystem::CompileVertexShader. HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "" << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_VERTEX_SHADER)
        std::wcout << L"[INFO] : Vertex shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyRenderSystem::CompilePixelShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
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
        std::cout << "D3DCompileFromFile failed in MyRenderSystem::CompilePixelShader. HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "" << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_PIXEL_SHADER)
        std::wcout << L"[INFO] : Pixel shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyRenderSystem::ReleaseCompiledShader() {
    if (this->temporaryBlob) {
        this->temporaryBlob->Release();
        this->temporaryBlob = nullptr;
    }
    return true;
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝