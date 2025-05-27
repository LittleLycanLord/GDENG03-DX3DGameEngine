#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_DEVICECONTEXT;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyDeviceContext::MyDeviceContext(ID3D11DeviceContext* D3DDeviceContext) {
    this->D3DDeviceContext = D3DDeviceContext;
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext constructed" << std::endl;
}
MyDeviceContext::~MyDeviceContext() {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyDeviceContext::ClearRenderTargetColor(MySwapChain* swapChain, MyVec4 color) {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::ClearRenderTargetColor called" << std::endl;
    if (!swapChain || !swapChain->D3D11RenderTargetView) {
        std::cout << "[ERROR] : swapChain or D3D11RenderTargetView is null in MyDeviceContext::ClearRenderTargetColor" << std::endl;
        return false;
    }
    if (!this->D3DDeviceContext) {
        std::cout << "[ERROR] : D3DDeviceContext is null in MyDeviceContext::ClearRenderTargetColor" << std::endl;
        return false;
    }
    FLOAT clearColor[4] = { color.x, color.y, color.z,  color.w };
    this->D3DDeviceContext->ClearRenderTargetView(
        swapChain->D3D11RenderTargetView,
        clearColor
    );
    this->D3DDeviceContext->OMSetRenderTargets(
        1,
        &swapChain->D3D11RenderTargetView,
        NULL
    );
    return true;
}

void MyDeviceContext::SetVertexBuffer(MyVertexBuffer* vertexBuffer) {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::SetVertexBuffer called" << std::endl;
    if (!vertexBuffer || !vertexBuffer->D3DVertexBuffer || !vertexBuffer->D3DInputLayout) {
        std::cout << "[ERROR] : vertexBuffer, vertexBuffer->vertexBuffer, or inputLayout is null in MyDeviceContext::SetVertexBuffer" << std::endl;
        return;
    }
    if (!this->D3DDeviceContext) {
        std::cout << "[ERROR] : D3DDeviceContext is null in MyDeviceContext::SetVertexBuffer" << std::endl;
        return;
    }
    UINT stride = vertexBuffer->vertexSize;
    UINT offset = 0;
    this->D3DDeviceContext->IASetVertexBuffers(
        0,
        1,
        &vertexBuffer->D3DVertexBuffer,
        &stride,
        &offset
    );
    this->D3DDeviceContext->IASetInputLayout(vertexBuffer->D3DInputLayout);
}

void MyDeviceContext::SetViewPortSize(UINT width, UINT height) {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::SetViewPortSize called" << std::endl;
    if (!this->D3DDeviceContext) {
        std::cout << "[ERROR] : D3DDeviceContext is null in MyDeviceContext::SetViewPortSize" << std::endl;
        return;
    }
    D3D11_VIEWPORT viewport;
    viewport.Width = (FLOAT)width;
    viewport.Height = (FLOAT)height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    this->D3DDeviceContext->RSSetViewports(1, &viewport);
}

void MyDeviceContext::SetVertexShader(MyVertexShader* vertexShader) {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::SetVertexShader called" << std::endl;
    if (!vertexShader || !vertexShader->D3DVertexShader) {
        std::cout << "[ERROR] : vertexShader or D3DVertexShader is null in MyDeviceContext::SetVertexShader" << std::endl;
        return;
    }
    if (!this->D3DDeviceContext) {
        std::cout << "[ERROR] : D3DDeviceContext is null in MyDeviceContext::SetVertexShader" << std::endl;
        return;
    }
    this->D3DDeviceContext->VSSetShader(
        vertexShader->D3DVertexShader,
        nullptr,
        0
    );
}

void MyDeviceContext::SetPixelShader(MyPixelShader* pixelShader) {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::SetPixelShader called" << std::endl;
    if (!pixelShader || !pixelShader->D3DPixelShader) {
        std::cout << "[ERROR] : pixelShader or D3DPixelShader is null in MyDeviceContext::SetPixelShader" << std::endl;
        return;
    }
    if (!this->D3DDeviceContext) {
        std::cout << "[ERROR] : D3DDeviceContext is null in MyDeviceContext::SetPixelShader" << std::endl;
        return;
    }
    this->D3DDeviceContext->PSSetShader(
        pixelShader->D3DPixelShader,
        nullptr,
        0
    );
}
void MyDeviceContext::SetConstantBuffer(MyVertexShader* vertexShader, MyConstantBuffer* constantBuffer) {
    this->D3DDeviceContext->VSSetConstantBuffers(
        0,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}
void MyDeviceContext::SetConstantBuffer(MyPixelShader* pixelShader, MyConstantBuffer* constantBuffer) {
    this->D3DDeviceContext->PSSetConstantBuffers(
        0,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}
void MyDeviceContext::DrawTriangle(UINT vertexCount, UINT startVertexIndex) {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::DrawTriangle called with vertexCount=" << vertexCount << ", startVertexIndex=" << startVertexIndex << std::endl;
    if (!this->D3DDeviceContext) {
        std::cout << "[ERROR] : D3DDeviceContext is null in MyDeviceContext::DrawTriangle" << std::endl;
        return;
    }
    this->D3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->D3DDeviceContext->Draw(vertexCount, startVertexIndex);
}

bool MyDeviceContext::Release() {
    if (LOG_INFO_DEVICECONTEXT) std::cout << "[INFO] : MyDeviceContext::Release called" << std::endl;
    if (this->D3DDeviceContext) {
        this->D3DDeviceContext->Release();
        this->D3DDeviceContext = nullptr;
        delete this;
    }
    else {
        std::cout << "[ERROR] : D3DDeviceContext is already null in MyDeviceContext::Release" << std::endl;
    }
    return true;
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
