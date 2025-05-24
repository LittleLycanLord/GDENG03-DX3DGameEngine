#include "Graphics/Shaders/MyPixelShader.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyPixelShader::MyPixelShader() {}
MyPixelShader::~MyPixelShader() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyPixelShader::Initialize(const void* shaderByteCode, size_t shaderSize) {
    HRESULT result = MyGraphicsEngine::GetInstance()->D3DDevice->CreatePixelShader(
        shaderByteCode,
        shaderSize,
        NULL,
        &this->D3DPixelShader
    );
    if (FAILED(result)) {
        std::cout << "[ERROR] : CreatePixelShader failed in MyPixelShader::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }
    return true;
}
bool MyPixelShader::Release() {
    if (this->D3DPixelShader) {
        this->D3DPixelShader->Release();
        this->D3DPixelShader = nullptr;
    }
    else {
        std::cout << "[ERROR] : D3DPixelShader is already null in MyPixelShader::Release" << std::endl;
    }
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
