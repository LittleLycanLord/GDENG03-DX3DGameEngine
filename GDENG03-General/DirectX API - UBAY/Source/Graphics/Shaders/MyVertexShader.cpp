#include "Graphics/Shaders/MyVertexShader.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyVertexShader::MyVertexShader() {}
MyVertexShader::~MyVertexShader() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyVertexShader::Initialize(const void* shaderByteCode, size_t shaderSize) {
    HRESULT result = MyGraphicsEngine::GetInstance()->D3DDevice->CreateVertexShader(
        shaderByteCode,
        shaderSize,
        NULL,
        &this->D3DVertexShader
    );
    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateVertexShader failed in MyVertexShader::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }
    return true;
}
bool MyVertexShader::Release() {
    if (this->D3DVertexShader) {
        this->D3DVertexShader->Release();
        this->D3DVertexShader = nullptr;
    }
    else {
        std::cout << "[ERROR] : D3DVertexShader is already null in MyVertexShader::Release" << std::endl;
    }
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
