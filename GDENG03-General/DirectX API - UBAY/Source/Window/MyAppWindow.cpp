#include "Window/MyAppWindow.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;
extern bool LOG_INFO_CONSTANTBUFFER;
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
void MyAppWindow::UpdateDeltaTime() {
    this->oldTime = this->newTime;
    this->newTime = ::GetTickCount();
    this->deltaTime = this->oldTime ? (this->newTime - this->oldTime) / 1000.0f : 0.0f;
}
void MyAppWindow::UpdateObjects() {
    this->constantData.time += this->deltaTime;

    float speedMultiplier = 1.0f;
    this->experimentalDelta += this->deltaTime * speedMultiplier;

    //* Test Translate
    // if (this->experimentalDelta > 1.0f)
    //     this->experimentalDelta = 0.0f;
    // this->constantData.world.Translate(MyVec3::Lerp(MyVec3(-2.0f, -2.0f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), this->experimentalDelta));

    //* Test Scale
    // this->constantData.world.Scale(MyVec3::Lerp(MyVec3(0.5f, 0.5f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), (sin(experimentalDelta) + 1.0f) / 2.0f));

    //* Transformation Matrix : T -> R -> S (Note: Matrix multiplication is not commutative)
    this->constantData.world.SetIdentity();
    this->constantData.world *= MyMatrix4x4::Scaling(MyVec3::Lerp(MyVec3(0.5f, 0.5f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), (sin(experimentalDelta) + 1.0f) / 2.0f));
    // this->constantData.world *= MyMatrix4x4::Rotating();
    this->constantData.world *= MyMatrix4x4::Translation(MyVec3::Lerp(MyVec3(-2.0f, -2.0f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), this->experimentalDelta * 0.1f));

    // this->constantData.view.SetIdentity();
    // this->constantData.projection.SetOrthographicLeftHand(
    //     (this->GetWindowRect().right - this->GetWindowRect().left) / 400.0f,
    //     (this->GetWindowRect().bottom - this->GetWindowRect().top) / 400.0f,
    //     -4.0f,
    //     4.0f
    // );
    this->constantBuffer->Update(MyGraphicsEngine::GetInstance()->GetImmedieateDeviceContext(), &this->constantData);
}

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

    //* Three Quads
    float offset = 0.3f;
    MyTriangle triangleA(
        MyVertex(
            MyVec3(-0.1f - offset, 0.1f - offset, 0.0f),  // position (x, y, z)
            MyVec3(-0.1f - offset, 0.1f - offset, 0.0f),  // nextPosition (x, y, z)
            MyVec3(1.0f, 0.0f, 0.0f),                     // color (r, g, b)
            MyVec3(0.0f, 1.0f, 0.0f)                      // nextColor (r, g, b)
        ), // Top-left
        MyVertex(
            MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // position
            MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // nextPosition
            MyVec3(0.0f, 1.0f, 0.0f),                    // color
            MyVec3(1.0f, 1.0f, 0.0f)                     // nextColor
        ), // Top-right
        MyVertex(
            MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // position
            MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // nextPosition
            MyVec3(0.0f, 0.0f, 1.0f),                     // color
            MyVec3(1.0f, 0.0f, 0.0f)                      // nextColor
        ) // Bottom-left
    );
    MyTriangle triangleB(
        MyVertex(
            MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // position
            MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // nextPosition
            MyVec3(0.0f, 0.0f, 1.0f),                     // color
            MyVec3(1.0f, 0.0f, 0.0f)                      // nextColor
        ), // Bottom-left
        MyVertex(
            MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // position
            MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // nextPosition
            MyVec3(0.0f, 1.0f, 0.0f),                    // color
            MyVec3(1.0f, 1.0f, 0.0f)                     // nextColor
        ), // Top-right
        MyVertex(
            MyVec3(0.1f - offset, -0.1f - offset, 0.0f), // position
            MyVec3(0.1f - offset, -0.1f - offset, 0.0f), // nextPosition
            MyVec3(1.0f, 1.0f, 0.0f),                    // color
            MyVec3(0.0f, 0.0f, 1.0f)                     // nextColor
        ) // Bottom-right
    );
    MyQuad quadA(triangleA, triangleB);

    MyQuad quadB;

    MyVertex topLeft(
        MyVec3(-0.1f + offset, 0.1f + offset, 0.0f),  // position (x, y, z)
        MyVec3(-0.1f + offset, 0.1f + offset, 0.0f),  // nextPosition (x, y, z)
        MyVec3(0.0f, 0.0f, 1.0f),                     // color (r, g, b)
        MyVec3(1.0f, 1.0f, 0.0f)                      // nextColor (r, g, b)
    );
    MyVertex topRight(
        MyVec3(0.1f + offset, 0.1f + offset, 0.0f),   // position (x, y, z)
        MyVec3(0.1f + offset, 0.1f + offset, 0.0f),   // nextPosition (x, y, z)
        MyVec3(0.0f, 1.0f, 0.0f),                     // color (r, g, b)
        MyVec3(0.0f, 0.0f, 1.0f)                      // nextColor (r, g, b)
    );
    MyVertex bottomRight(
        MyVec3(0.1f + offset, -0.1f + offset, 0.0f),  // position (x, y, z)
        MyVec3(0.1f + offset, -0.1f + offset, 0.0f),  // nextPosition (x, y, z)
        MyVec3(0.0f, 0.0f, 1.0f),                     // color (r, g, b)
        MyVec3(0.0f, 1.0f, 0.0f)                      // nextColor (r, g, b)
    );
    MyVertex bottomLeft(
        MyVec3(-0.1f + offset, -0.1f + offset, 0.0f), // position (x, y, z)
        MyVec3(-0.1f + offset, -0.1f + offset, 0.0f), // nextPosition (x, y, z)
        MyVec3(1.0f, 1.0f, 0.0f),                     // color (r, g, b)
        MyVec3(0.0f, 0.0f, 1.0f)                      // nextColor (r, g, b)
    );
    MyQuad quadC(topLeft, topRight, bottomRight, bottomLeft);

    MyVertex vertices[100];
    int i = 0;
    for (MyVertex vertex : quadA.GetVertices()) {
        vertices[i] = vertex;
        i++;
    }
    for (MyVertex vertex : quadB.GetVertices()) {
        vertices[i] = vertex;
        i++;
    }
    for (MyVertex vertex : quadC.GetVertices()) {
        vertices[i] = vertex;
        i++;
    }

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

    if (LOG_INFO_CONSTANTBUFFER) std::cout << "[INFO] : Setting constant buffer" << std::endl;
    this->constantData.time = 0;
    this->constantData.world.Translate(MyVec3(0.0f, 0.0f, 0.0f));
    this->constantData.view.SetIdentity();
    this->constantData.projection.SetOrthographicLeftHand(
        (this->GetWindowRect().right - this->GetWindowRect().left) / 400.0f,
        (this->GetWindowRect().bottom - this->GetWindowRect().top) / 400.0f,
        -4.0f,
        4.0
    );
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


    this->UpdateObjects();

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

    this->UpdateDeltaTime();
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