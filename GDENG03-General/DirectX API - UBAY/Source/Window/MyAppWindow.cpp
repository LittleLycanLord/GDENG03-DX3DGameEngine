#include "Window/MyAppWindow.hpp"
#include "Math/Vec4.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyAppWindow::MyAppWindow() {}
MyAppWindow::~MyAppWindow() {}

//* ╔═════════════════════════════════╗
//* ║ Magical Shit I Don't Understand ║
//* ╚═════════════════════════════════╝

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyAppWindow::OnCreate() {
    MyWindow::OnCreate();
    MyGraphicsEngine::GetInstance()->Initialize();
    RECT windowRectangle = this->GetWindowRect();
    swapChain = MyGraphicsEngine::GetInstance()->CreateSwapChain();
    swapChain->Initialize(this->windowHandle, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top);
}
void MyAppWindow::OnUpdate() {
    MyWindow::OnUpdate();
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->ClearRenderTargetColor(this->swapChain, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    if (this->swapChain)
        this->swapChain->Present(false);
}
void MyAppWindow::OnDestroy() {
    MyGraphicsEngine::GetInstance()->Release();
    if (this->swapChain) {
        this->swapChain->Release();
        delete this->swapChain;
        this->swapChain = nullptr;
    }
    MyWindow::OnDestroy();
}