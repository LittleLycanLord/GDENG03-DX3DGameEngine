#include "Graphics/MyVertexBuffer.h"

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyVertexBuffer::MyVertexBuffer() {}
DX3D::MyVertexBuffer::~MyVertexBuffer() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool DX3D::MyVertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader) {
    if (buffer) buffer->Release();
    if (layout) layout->Release();

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = size_vertex * size_list;
    bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA bufferData = {};
    bufferData.pSysMem = list_vertices;

    this->size_vertex = size_vertex;
    this->size_list = size_list;

    // if (FAILED(MyGraphicsEngine::getGraphicsDevice()->getDevice()->d3dDevice->CreateBuffer(&bufferDescription, &bufferData, &vertexBuffer))) {
    //     return false;
    // }

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    UINT size_layout = ARRAYSIZE(layout);

    // if (FAILED(MyGraphicsEngine::getGraphicsDevice()->getDevice()->d3dDevice->CreateInputLayout(
    //     layout,
    //     size_layout,
    //     shader_byte_code,
    //     size_byte_shader,
    //     &vertexBuffer
    // ))) {
    //     return false;
    // }


    return true;
}
bool DX3D::MyVertexBuffer::release() {
    buffer->Release();
    layout->Release();
    delete this;
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝