#include "Graphics/Buffers/MyVertexBuffer.hpp"

using namespace DX3D;

extern bool LOG_INFO_VERTEXBUFFER;

MyVertexBuffer::MyVertexBuffer() {
    if (LOG_INFO_VERTEXBUFFER) std::cout << "[INFO] : MyVertexBuffer constructed" << std::endl;
}
MyVertexBuffer::~MyVertexBuffer() {
    if (LOG_INFO_VERTEXBUFFER) std::cout << "[INFO] : MyVertexBuffer destructed" << std::endl;
}

bool MyVertexBuffer::Load(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize) {
    if (LOG_INFO_VERTEXBUFFER) std::cout << "[INFO] : MyVertexBuffer::Load called" << std::endl;

    if (this->D3DInputLayout) this->D3DInputLayout->Release();
    if (this->D3DVertexBuffer) this->D3DVertexBuffer->Release();

    ID3D11Device* D3DDevice = MyGraphicsEngine::GetInstance()->D3DDevice;

    if (!D3DDevice) {
        std::cout << "[ERROR] : D3DDevice is null in MyVertexBuffer::Load" << std::endl;
        return false;
    }

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = vertexSize * vertexCount;
    bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = vertexList;

    this->vertexSize = vertexSize;
    this->vertexCount = vertexCount;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &vertexData,
        &this->D3DVertexBuffer
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateBuffer failed in MyVertexBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        // { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 position (offset 0)
        // { "POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 nextPosition (offset 12)
        // { "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 color (offset 24)
        // { "COLOR",    1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 nextColor (offset 36)

        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 position (offset 0)
        { "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // float3 nextPosition (offset 12)
        { "COLOR",    1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 color (offset 24)
    };

    result = D3DDevice->CreateInputLayout(
        layout,
        ARRAYSIZE(layout),
        shaderByteCode,
        shaderByteCodeSize,
        &this->D3DInputLayout
    );

    if (FAILED(result)) {
        std::cout << "[ERROR] : CreateInputLayout failed in MyVertexBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
        return false;
    }

    if (LOG_INFO_VERTEXBUFFER)
        std::cout << "[INFO] : Vertex buffer and input layout created successfully" << std::endl;

    return SUCCEEDED(result);
}
bool MyVertexBuffer::Release() {
    if (LOG_INFO_VERTEXBUFFER) std::cout << "[INFO] : MyVertexBuffer::Release called" << std::endl;

    if (this->D3DInputLayout) this->D3DInputLayout->Release();
    if (this->D3DVertexBuffer) this->D3DVertexBuffer->Release();
    return true;
}

