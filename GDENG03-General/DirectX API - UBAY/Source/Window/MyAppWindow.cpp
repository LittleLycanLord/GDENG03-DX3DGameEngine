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
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnCreate called" << std::endl;

    MyWindow::OnCreate();
    MyGraphicsEngine::GetInstance()->Initialize();
    RECT windowRectangle = this->GetWindowRect();
    swapChain = MyGraphicsEngine::GetInstance()->CreateSwapChain();
    swapChain->Initialize(this->windowHandle, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top);

    //! Note: Define vertices in a CLOCKWISE MANNER

    // // * Single Color Triangle
    // MyVertex vertices[] = {
    //     MyVertex(
    //         0.0f,  0.5f, 0.0f    // position (x, y, z)
    //     ), // Top
    //     MyVertex(
    //         0.5f, -0.5f, 0.0f    // position
    //     ), // Right
    //     MyVertex(
    //        -0.5f, -0.5f, 0.0f    // position
    //     ), // Left
    // };

    // //* Single Color Rectangle
    // MyVertex vertices[] = {
    //     MyVertex(
    //        -0.5f,  0.5f, 0.0f    // position
    //     ), // Top-left
    //     MyVertex(
    //         0.5f,  0.5f, 0.0f    // position
    //     ), // Top-right
    //     MyVertex(
    //        -0.5f, -0.5f, 0.0f    // position
    //     ), // Bottom-left

    //     MyVertex(
    //        -0.5f, -0.5f, 0.0f    // position
    //     ), // Bottom-left
    //     MyVertex(
    //         0.5f,  0.5f, 0.0f    // position
    //     ), // Top-right
    //     MyVertex(
    //         0.5f, -0.5f, 0.0f    // position
    //     ), // Bottom-right
    // };

    // //* Rainbow Triangle
    // MyVertex vertices[] = {
    //     MyVertex(
    //         0.0f,  0.5f, 0.0f,    // position
    //         1.0f,  0.0f, 0.0f     // color
    //     ), // Top
    //     MyVertex(
    //         0.5f, -0.5f, 0.0f,    // position
    //         0.0f,  0.0f, 1.0f     // color
    //     ), // Right
    //     MyVertex(
    //        -0.5f, -0.5f, 0.0f,    // position
    //         0.0f,  1.0f, 0.0f     // color
    //     ), // Left
    // };

    // //* Rainbow Rectangle
    // MyVertex vertices[] = {
    //     MyVertex(
    //        -0.5f,  0.5f, 0.0f,    // position
    //         0.0f,  1.0f, 0.0f     // color
    //     ), // Top-left
    //     MyVertex(
    //         0.5f,  0.5f, 0.0f,    // position
    //         1.0f,  1.0f, 0.0f     // color
    //     ), // Top-right
    //     MyVertex(
    //        -0.5f, -0.5f, 0.0f,    // position
    //         1.0f,  0.0f, 0.0f     // color
    //     ), // Bottom-left

    //     MyVertex(
    //        -0.5f, -0.5f, 0.0f,    // position
    //         1.0f,  0.0f, 0.0f     // color
    //     ), // Bottom-left
    //     MyVertex(
    //         0.5f,  0.5f, 0.0f,    // position
    //         1.0f,  1.0f, 0.0f     // color
    //     ), // Top-right
    //     MyVertex(
    //         0.5f, -0.5f, 0.0f,    // position
    //         0.0f,  0.0f, 1.0f     // color
    //     ), // Bottom-right
    // };

    // //* Animated Rectangle
    // MyVertex vertices[] = {
    //     MyVertex(
    //         -0.5f,  0.5f, 0.0f,    // position (x, y, z)
    //         -0.11f, 0.78f, 0.0f,   // nextPosition (x, y, z)
    //          0.0f,  1.0f, 0.0f     // color (r, g, b)
    //     ), // Top-left
    //     MyVertex(
    //          0.5f,  0.5f, 0.0f,    // position
    //          0.88f, 0.77f, 0.0f,   // nextPosition
    //          1.0f,  1.0f, 0.0f     // color
    //     ), // Top-right
    //     MyVertex(
    //         -0.5f, -0.5f, 0.0f,    // position
    //         -0.32f,-0.11f, 0.0f,   // nextPosition
    //          1.0f,  0.0f, 0.0f     // color
    //     ), // Bottom-left

    //     MyVertex(
    //         -0.5f, -0.5f, 0.0f,    // position
    //         -0.32f,-0.11f, 0.0f,   // nextPosition
    //          1.0f,  0.0f, 0.0f     // color
    //     ), // Bottom-left
    //     MyVertex(
    //          0.5f,  0.5f, 0.0f,    // position
    //          0.88f, 0.77f, 0.0f,   // nextPosition
    //          1.0f,  1.0f, 0.0f     // color
    //     ), // Top-right
    //     MyVertex(
    //          0.5f, -0.5f, 0.0f,    // position
    //          0.75f, -0.73f, 0.0f,  // nextPosition
    //          0.0f,  0.0f, 1.0f     // color
    //     ), // Bottom-right
    // };

    //* Animated Color Changing Rectangle
    MyVertex vertices[] = {
        MyVertex(
            -0.5f,  0.5f, 0.0f,    // position (x, y, z)
            -0.11f, 0.78f, 0.0f,   // nextPosition (x, y, z)
             0.0f,  1.0f, 0.0f,    // color (r, g, b)
             1.0f,  0.0f, 0.0f     // nextColor (r, g, b)
        ), // Top-left
        MyVertex(
             0.5f,  0.5f, 0.0f,    // position
             0.88f, 0.77f, 0.0f,   // nextPosition
             1.0f,  1.0f, 0.0f,    // color
             0.0f,  1.0f, 0.0f     // nextColor
        ), // Top-right
        MyVertex(
            -0.5f, -0.5f, 0.0f,    // position
            -0.32f,-0.11f, 0.0f,   // nextPosition
             1.0f,  0.0f, 0.0f,    // color
             0.0f,  0.0f, 1.0f     // nextColor
        ), // Bottom-left

        MyVertex(
            -0.5f, -0.5f, 0.0f,    // position
            -0.32f,-0.11f, 0.0f,   // nextPosition
             1.0f,  0.0f, 0.0f,    // color
             0.0f,  0.0f, 1.0f     // nextColor
        ), // Bottom-left
        MyVertex(
             0.5f,  0.5f, 0.0f,    // position
             0.88f, 0.77f, 0.0f,   // nextPosition
             1.0f,  1.0f, 0.0f,    // color
             0.0f,  1.0f, 0.0f     // nextColor
        ), // Top-right
        MyVertex(
             0.5f, -0.5f, 0.0f,    // position
             0.75f, -0.73f, 0.0f,  // nextPosition
             0.0f,  0.0f, 1.0f,    // color
             1.0f,  1.0f, 0.0f     // nextColor
        ), // Bottom-right
    };

    vertexBuffer = MyGraphicsEngine::GetInstance()->CreateVertexBuffer();
    if (!vertexBuffer) {
        std::cout << "[ERROR] : Failed to create vertexBuffer!" << std::endl;
        return;
    }

    // Compile and create vertex shader
    void* vertexShaderByteCode = nullptr;
    size_t vertexShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->CompileVertexShader(
        VERTEX_SHADER_DIRECTORY.c_str(), "main", &vertexShaderByteCode, &vertexShaderSize)) {
        std::cout << "[ERROR] : Failed to compile vertex shader!" << std::endl;
        return;
    }
    this->vertexShader = MyGraphicsEngine::GetInstance()->CreateVertexShader(vertexShaderByteCode, vertexShaderSize);
    if (!this->vertexShader) {
        std::cout << "[ERROR] : Failed to create vertexShader!" << std::endl;
        return;
    }
    if (!this->vertexBuffer->Load(vertices, sizeof(MyVertex), ARRAYSIZE(vertices), vertexShaderByteCode, vertexShaderSize)) {
        std::cout << "[ERROR] : vertexBuffer->Load failed!" << std::endl;
        return;
    }
    MyGraphicsEngine::GetInstance()->ReleaseCompiledShader();

    // Compile and create pixel shader
    void* pixelShaderByteCode = nullptr;
    size_t pixelShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->CompilePixelShader(
        PIXEL_SHADER_DIRECTORY.c_str(), "main", &pixelShaderByteCode, &pixelShaderSize)) {
        std::cout << "[ERROR] : Failed to compile pixel shader!" << std::endl;
        return;
    }
    this->pixelShader = MyGraphicsEngine::GetInstance()->CreatePixelShader(pixelShaderByteCode, pixelShaderSize);
    if (!this->pixelShader) {
        std::cout << "[ERROR] : Failed to create pixelShader!" << std::endl;
        return;
    }
    MyGraphicsEngine::GetInstance()->ReleaseCompiledShader();

    MyConstant constantData;
    constantData.angle = 0;
    this->constantBuffer = MyGraphicsEngine::GetInstance()->CreateConstantBuffer();
    if (!this->constantBuffer) {
        std::cout << "[ERROR] : Failed to create constantBuffer!" << std::endl;
        return;
    }
    if (!this->constantBuffer->Load(&constantData, sizeof(MyConstant))) {
        std::cout << "[ERROR] : constantBuffer->Load failed!" << std::endl;
        return;
    }
}

void MyAppWindow::OnUpdate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnUpdate called" << std::endl;

    MyWindow::OnUpdate();
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : OnUpdate called" << std::endl;
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->ClearRenderTargetColor(this->swapChain, MyVec4(0.0f, 0.3f, 0.4f, 1.0f));

    RECT windowRectangle = this->GetWindowRect();
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetViewPortSize(windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top);

    // Set constant buffer
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Setting constant buffer" << std::endl;
    unsigned long newTime = 0;
    if (this->oldTime)
        newTime = ::GetTickCount() - this->oldTime;
    this->deltaTime = newTime / 1000.0f;
    this->oldTime = ::GetTickCount();
    this->angle += 1.57f * this->deltaTime;

    MyConstant constantData;
    constantData.angle = this->angle;
    this->constantBuffer->Update(MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext(), &constantData);
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);

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
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnDestroy called" << std::endl;

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