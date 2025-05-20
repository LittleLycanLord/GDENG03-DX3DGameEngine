#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyDeviceContext::MyDeviceContext(ID3D11DeviceContext* D3DDeviceContext) {
    this->D3DDeviceContext = D3DDeviceContext;
}
MyDeviceContext::~MyDeviceContext() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyDeviceContext::ClearRenderTargetColor(MySwapChain* swapChain, Vec4 color) {
    FLOAT clearColor[4] = { color.w, color.x, color.y, color.z };
    this->D3DDeviceContext->ClearRenderTargetView(
        swapChain->D3D11RenderTargetView,
        clearColor
    );
    return true;
}
bool MyDeviceContext::Release() {
    if (D3DDeviceContext) {
        this->D3DDeviceContext->Release();
        this->D3DDeviceContext = nullptr;
        delete this;
    }
    return true;
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
