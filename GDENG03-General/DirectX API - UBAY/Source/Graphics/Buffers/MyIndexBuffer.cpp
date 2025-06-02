#include "Graphics/Buffers/MyIndexBuffer.hpp"

using namespace DX3D;

extern bool LOG_INFO_INDEXBUFFER;

MyIndexBuffer::MyIndexBuffer() {
    if (LOG_INFO_INDEXBUFFER) std::cout << "[INFO] : MyIndexBuffer constructed" << std::endl;
}
MyIndexBuffer::~MyIndexBuffer() {
    if (LOG_INFO_INDEXBUFFER) std::cout << "[INFO] : MyIndexBuffer destructed" << std::endl;
}

bool MyIndexBuffer::Load(void* indices, UINT indexCount) {
    if (LOG_INFO_INDEXBUFFER) std::cout << "[INFO] : MyIndexBuffer::Load called" << std::endl;

    if (this->D3DIndexBuffer) {
        if (LOG_INFO_INDEXBUFFER) std::cout << "[INFO] : Releasing previous D3DIndexBuffer in MyIndexBuffer::Load" << std::endl;
        this->D3DIndexBuffer->Release();
        this->D3DIndexBuffer = nullptr;
    }

    ID3D11Device* D3DDevice = MyGraphicsEngine::GetInstance()->D3DDevice;

    if (!D3DDevice) {
        std::cout << "[ERROR] : D3DDevice is null in MyIndexBuffer::Load" << std::endl;
        return false;
    }
    if (!indices) {
        std::cout << "[ERROR] : indices pointer is null in MyIndexBuffer::Load" << std::endl;
        return false;
    }
    if (indexCount == 0) {
        std::cout << "[ERROR] : indexCount is zero in MyIndexBuffer::Load" << std::endl;
        return false;
    }

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = 4 * indexCount;
    bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;
    this->indexCount = indexCount;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &indexData,
        &this->D3DIndexBuffer
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateBuffer failed in MyIndexBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    if (LOG_INFO_INDEXBUFFER)
        std::cout << "[INFO] : Index buffer created successfully" << std::endl;

    return SUCCEEDED(result);
}
bool MyIndexBuffer::Release() {
    if (LOG_INFO_INDEXBUFFER) std::cout << "[INFO] : MyIndexBuffer::Release called" << std::endl;

    if (this->D3DIndexBuffer) {
        this->D3DIndexBuffer->Release();
        this->D3DIndexBuffer = nullptr;
        if (LOG_INFO_INDEXBUFFER)
            std::cout << "[INFO] : Index buffer released" << std::endl;
    } else {
        std::cout << "[ERROR] : D3DIndexBuffer is already null in MyIndexBuffer::Release" << std::endl;
    }
    return true;
}

