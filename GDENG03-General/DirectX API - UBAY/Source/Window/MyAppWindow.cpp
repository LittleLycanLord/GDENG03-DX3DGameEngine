#include "Window/MyAppWindow.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;
// Add extern declarations for shader path constants
extern const std::wstring VERTEX_SHADER_DIRECTORY;
extern const std::wstring PIXEL_SHADER_DIRECTORY;

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

    //! Note: Define vertices in a CLOCKWISE MANNER

    // // * Single Color Triangle
    // MyVertex vertices[] = {
    //     MyVertex(0.0f,  0.5f, 0.0f), // Top
    //     MyVertex(0.5f, -0.5f, 0.0f), // Right
    //     MyVertex(-0.5f,  -0.5f, 0.0f), // Left
    // };

    // //* Single Color Rectangle
    // MyVertex vertices[] = {
    //     MyVertex(-0.5f,  0.5f, 0.0f), // Top-left
    //     MyVertex(0.5f,  0.5f, 0.0f), // Top-right
    //     MyVertex(-0.5f, -0.5f, 0.0f), // Bottom-left

    //     MyVertex(-0.5f, -0.5f, 0.0f), // Bottom-left
    //     MyVertex(0.5f,  0.5f, 0.0f), // Top-right
    //     MyVertex(0.5f, -0.5f, 0.0f), // Bottom-right
    // };

    // //* Rainbow Triangle
    // MyVertex vertices[] = {
    //     MyVertex(0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f), // Top
    //     MyVertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f), // Right
    //     MyVertex(-0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f), // Left
    // };

    //* Rainbow Rectangle
    MyVertex vertices[] = {
        MyVertex(-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f), // Top-left
        MyVertex(0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f), // Top-right
        MyVertex(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f), // Bottom-left

        MyVertex(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f), // Bottom-left
        MyVertex(0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f), // Top-right
        MyVertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f), // Bottom-right
    };

    vertexBuffer = MyGraphicsEngine::GetInstance()->CreateVertexBuffer();

    // Compile and create vertex shader
    void* vertexShaderByteCode = nullptr;
    size_t vertexShaderSize = 0;
    MyGraphicsEngine::GetInstance()->CompileVertexShader(
        VERTEX_SHADER_DIRECTORY.c_str(), "main", &vertexShaderByteCode, &vertexShaderSize);
    vertexShader = MyGraphicsEngine::GetInstance()->CreateVertexShader(vertexShaderByteCode, vertexShaderSize);
    vertexBuffer->Load(vertices, sizeof(MyVertex), ARRAYSIZE(vertices), vertexShaderByteCode, vertexShaderSize);
    MyGraphicsEngine::GetInstance()->ReleaseCompiledShader();

    // Compile and create pixel shader
    void* pixelShaderByteCode = nullptr;
    size_t pixelShaderSize = 0;
    MyGraphicsEngine::GetInstance()->CompilePixelShader(
        PIXEL_SHADER_DIRECTORY.c_str(), "main", &pixelShaderByteCode, &pixelShaderSize);
    pixelShader = MyGraphicsEngine::GetInstance()->CreatePixelShader(pixelShaderByteCode, pixelShaderSize);

    MyGraphicsEngine::GetInstance()->ReleaseCompiledShader();
}

void MyAppWindow::OnUpdate() {
    MyWindow::OnUpdate();
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : OnUpdate called" << std::endl;
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->ClearRenderTargetColor(this->swapChain, MyVec4(0.0f, 0.3f, 0.4f, 1.0f));

    RECT windowRectangle = this->GetWindowRect();
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetViewPortSize(windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top);

    // Set shaders before drawing
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Setting vertex and pixel shaders" << std::endl;
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetVertexShader(this->vertexShader);
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetPixelShader(this->pixelShader);

    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Setting vertex buffer: " << this->vertexBuffer << std::endl;
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetVertexBuffer(this->vertexBuffer);

    // Draw non-indexed
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->DrawTriangle(this->vertexBuffer->GetVertexCount(), 0);

    if (this->swapChain) {
        if (LOG_INFO_WINDOW) std::cout << "[INFO] : Presenting swap chain" << std::endl;
        this->swapChain->Present(true);
    }
}

void MyAppWindow::OnDestroy() {
    MyWindow::OnDestroy();
    if (this->vertexBuffer) {
        this->vertexBuffer->Release();
        delete this->vertexBuffer;
        this->vertexBuffer = nullptr;
    }
    if (this->vertexShader) {
        this->vertexShader->Release();
        delete this->vertexShader;
        this->vertexShader = nullptr;
    }
    if (this->pixelShader) {
        this->pixelShader->Release();
        delete this->pixelShader;
        this->pixelShader = nullptr;
    }
    if (this->swapChain) {
        this->swapChain->Release();
        delete this->swapChain;
        this->swapChain = nullptr;
    }
    MyGraphicsEngine::GetInstance()->Release();
}