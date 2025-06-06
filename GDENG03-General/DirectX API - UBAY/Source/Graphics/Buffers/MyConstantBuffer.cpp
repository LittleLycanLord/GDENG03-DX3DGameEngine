#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/MyGraphicsEngine.hpp"

using namespace DX3D;

extern bool LOG_INFO_VERTEX_BUFFER;
extern bool LOG_INFO_CONSTANT_BUFFER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyConstantBuffer::MyConstantBuffer(void* buffer, UINT bufferSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    if (LOG_INFO_CONSTANT_BUFFER) std::cout << "[INFO] : MyConstantBuffer constructed" << std::endl;

    ID3D11Device* D3DDevice = this->renderSystem->D3DDevice;

    if (!D3DDevice) {
        std::cerr << "[ERROR] D3DDevice is null in MyConstantBuffer::Load" << std::endl;
        throw std::exception("D3DDevice is null in MyConstantBuffer::Load");
    }

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = bufferSize;
    bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA constantData = {};
    constantData.pSysMem = buffer;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &constantData,
        &this->D3DConstantBuffer
    );

    if (FAILED(result)) {
        std::cout << "CreateBuffer failed in MyConstantBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR] : " << err.ErrorMessage() << std::endl;
    }

    if (LOG_INFO_CONSTANT_BUFFER)
        std::cout << "[INFO] : Constant buffer created successfully" << std::endl;

}
MyConstantBuffer::~MyConstantBuffer() {
    if (LOG_INFO_CONSTANT_BUFFER) std::cout << "[INFO] : MyConstantBuffer destructed" << std::endl;

    if (this->D3DConstantBuffer) {
        this->D3DConstantBuffer->Release();
        this->D3DConstantBuffer = nullptr;
        if (LOG_INFO_CONSTANT_BUFFER)
            std::cout << "[INFO] : Constant buffer released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyConstantBuffer::Update(MyDeviceContextPtr deviceContext, void* buffer) {
    if (LOG_INFO_CONSTANT_BUFFER)
        std::cout << "[INFO] : Updating constant buffer..." << std::endl;
    deviceContext->D3DDeviceContext->UpdateSubresource(
        this->D3DConstantBuffer,
        NULL,
        NULL,
        buffer,
        NULL,
        NULL
    );
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
