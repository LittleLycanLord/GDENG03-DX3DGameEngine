#include "Graphics/MyConstantBuffer.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

extern bool LOG_INFO_VERTEXBUFFER;
extern bool LOG_INFO_CONSTANTBUFFER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyConstantBuffer::MyConstantBuffer() {
    if (LOG_INFO_CONSTANTBUFFER) std::cout << "[INFO] : MyConstantBuffer constructed" << std::endl;
}
MyConstantBuffer::~MyConstantBuffer() {
    if (LOG_INFO_CONSTANTBUFFER) std::cout << "[INFO] : MyConstantBuffer destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyConstantBuffer::Load(void* buffer, UINT bufferSize) {
    if (LOG_INFO_CONSTANTBUFFER) std::cout << "[INFO] : MyConstantBuffer::Load called" << std::endl;

    if (this->D3DConstantBuffer) this->D3DConstantBuffer->Release();

    ID3D11Device* D3DDevice = MyGraphicsEngine::GetInstance()->D3DDevice;

    if (!D3DDevice) {
        std::cout << "[ERROR] : D3DDevice is null in MyConstantBuffer::Load" << std::endl;
        return false;
    }

    D3D11_BUFFER_DESC bufferDescription;
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = bufferSize;
    bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA constantData;
    constantData.pSysMem = buffer;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &constantData,
        &this->D3DConstantBuffer
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateBuffer failed in MyConstantBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    if (LOG_INFO_CONSTANTBUFFER)
        std::cout << "[INFO] : Constant buffer created successfully" << std::endl;

    return SUCCEEDED(result);
}
void MyConstantBuffer::Update(MyDeviceContext* deviceContext, void* buffer) {
    if (LOG_INFO_CONSTANTBUFFER) std::cout << "[INFO] : MyConstantBuffer::Update called" << std::endl;

    if (LOG_INFO_CONSTANTBUFFER)
        std::cout << "[INFO] : Updating constant buffer" << std::endl;
    deviceContext->D3DDeviceContext->UpdateSubresource(
        this->D3DConstantBuffer,
        NULL,
        NULL,
        buffer,
        NULL,
        NULL
    );
}
bool MyConstantBuffer::Release() {
    if (LOG_INFO_CONSTANTBUFFER) std::cout << "[INFO] : MyConstantBuffer::Release called" << std::endl;

    if (this->D3DConstantBuffer) {
        this->D3DConstantBuffer->Release();
        this->D3DConstantBuffer = nullptr;
        if (LOG_INFO_CONSTANTBUFFER)
            std::cout << "[INFO] : Constant buffer released" << std::endl;
    }
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
