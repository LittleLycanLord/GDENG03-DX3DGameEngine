#include "Window/MyAppWindow.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;
extern bool LOG_INFO_CONSTANT_BUFFER;
extern bool LOG_INFO_INPUT_SYSTEM_KEYBOARD;
extern bool LOG_INFO_INPUT_SYSTEM_MOUSE;
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
    this->newTime = ::GetTickCount64();
    this->deltaTime = this->oldTime ? (this->newTime - this->oldTime) / 1000.0f : 0.0f;
}
void MyAppWindow::UpdateObjects() {
    this->constantData.time += this->deltaTime;

    float speedMultiplier = 1.0f;
    this->experimentalDelta += this->deltaTime * speedMultiplier;

    // //* Test Translate
    // if (this->experimentalDelta > 1.0f)
    //     this->experimentalDelta = 0.0f;
    // this->constantData.world.Translate(MyVec3::Lerp(MyVec3(-2.0f, -2.0f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), this->experimentalDelta));

    // //* Test Scale
    // this->constantData.world.Scale(MyVec3::Lerp(MyVec3(0.5f, 0.5f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), (sin(experimentalDelta) + 1.0f) / 2.0f));

    // //* Transformation Matrix : T -> R -> S (Note: Matrix multiplication is not commutative)
    // this->constantData.world.SetIdentity();
    // this->constantData.world *= MyMatrix4x4::Scaling(MyVec3::Lerp(MyVec3(0.5f, 0.5f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), (sin(experimentalDelta) + 1.0f) / 2.0f));
    // // this->constantData.world *= MyMatrix4x4::Rotating();
    // this->constantData.world *= MyMatrix4x4::Translation(MyVec3::Lerp(MyVec3(-2.0f, -2.0f, 0.0f), MyVec3(2.0f, 2.0f, 0.0f), this->experimentalDelta * 0.1f));

    this->constantData.world.Scale(MyVec3(1.0f, 1.0f, 1.0f));

    //* Auto Rotating Cube
    // this->constantData.world *= MyMatrix4x4::RotationZ(this->experimentalDelta * 0.55f);
    // this->constantData.world *= MyMatrix4x4::RotationY(this->experimentalDelta * 0.55f);
    // this->constantData.world *= MyMatrix4x4::RotationX(this->experimentalDelta * 0.55f);

    // //* WASD Movement + Mouse Rotation
    // this->constantData.world *= MyMatrix4x4::RotationZ(0.0f);
    // this->constantData.world *= MyMatrix4x4::RotationY(this->yRotation);
    // this->constantData.world *= MyMatrix4x4::RotationX(this->xRotation);

    //* Camera Matrix
    this->cameraMatrix.SetIdentity();
    this->cameraMatrix *= MyMatrix4x4::RotationX(this->cameraRotation.x);
    this->cameraMatrix *= MyMatrix4x4::RotationY(this->cameraRotation.y);
    this->cameraMatrix *= MyMatrix4x4::RotationZ(this->cameraRotation.z);
    this->cameraPosition += this->cameraMatrix.GetTranslation() +
        (this->cameraMatrix.GetZDirection() * this->cameraMoveInput.y * this->moveSpeed * this->deltaTime) +
        (this->cameraMatrix.GetYDirection() * this->cameraMoveInput.z * this->moveSpeed * this->deltaTime) +
        (this->cameraMatrix.GetXDirection() * this->cameraMoveInput.x * this->moveSpeed * this->deltaTime);
    this->cameraMatrix *= MyMatrix4x4::Translation(this->cameraPosition);
    this->cameraMatrix.SetInverse();

    this->constantData.view = this->cameraMatrix;

    this->constantBuffer->Update(MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext(), &this->constantData);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyAppWindow::OnCreate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnCreate called" << std::endl;

    MyWindow::OnCreate();

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : Registering MyAppWindow as input listener" << std::endl;
    MyInputSystem::GetInstance()->AddListener(this);
    MyInputSystem::GetInstance()->SetCursorVisibility(false);
    MyGraphicsEngine::GetInstance()->Initialize();
    
    RECT windowRectangle = this->GetWindowRect();
    swapChain = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateSwapChain(this->windowHandle, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top);

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

    // //* Three Quads
    // float offset = 0.3f;
    // MyTriangle triangleA(
    //     MyVertex(
    //         MyVec3(-0.1f - offset, 0.1f - offset, 0.0f),  // position (x, y, z)
    //         MyVec3(-0.1f - offset, 0.1f - offset, 0.0f),  // nextPosition (x, y, z)
    //         MyVec3(1.0f, 0.0f, 0.0f),                     // color (r, g, b)
    //         MyVec3(0.0f, 1.0f, 0.0f)                      // nextColor (r, g, b)
    //     ), // Top-left
    //     MyVertex(
    //         MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // position
    //         MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // nextPosition
    //         MyVec3(0.0f, 1.0f, 0.0f),                    // color
    //         MyVec3(1.0f, 1.0f, 0.0f)                     // nextColor
    //     ), // Top-right
    //     MyVertex(
    //         MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // position
    //         MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // nextPosition
    //         MyVec3(0.0f, 0.0f, 1.0f),                     // color
    //         MyVec3(1.0f, 0.0f, 0.0f)                      // nextColor
    //     ) // Bottom-left
    // );
    // MyTriangle triangleB(
    //     MyVertex(
    //         MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // position
    //         MyVec3(-0.1f - offset, -0.1f - offset, 0.0f), // nextPosition
    //         MyVec3(0.0f, 0.0f, 1.0f),                     // color
    //         MyVec3(1.0f, 0.0f, 0.0f)                      // nextColor
    //     ), // Bottom-left
    //     MyVertex(
    //         MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // position
    //         MyVec3(0.1f - offset, 0.1f - offset, 0.0f),  // nextPosition
    //         MyVec3(0.0f, 1.0f, 0.0f),                    // color
    //         MyVec3(1.0f, 1.0f, 0.0f)                     // nextColor
    //     ), // Top-right
    //     MyVertex(
    //         MyVec3(0.1f - offset, -0.1f - offset, 0.0f), // position
    //         MyVec3(0.1f - offset, -0.1f - offset, 0.0f), // nextPosition
    //         MyVec3(1.0f, 1.0f, 0.0f),                    // color
    //         MyVec3(0.0f, 0.0f, 1.0f)                     // nextColor
    //     ) // Bottom-right
    // );
    // MyQuad quadA(triangleA, triangleB);

    // MyQuad quadB;

    // MyVertex topLeft(
    //     MyVec3(-0.1f + offset, 0.1f + offset, 0.0f),  // position (x, y, z)
    //     MyVec3(-0.1f + offset, 0.1f + offset, 0.0f),  // nextPosition (x, y, z)
    //     MyVec3(0.0f, 0.0f, 1.0f),                     // color (r, g, b)
    //     MyVec3(1.0f, 1.0f, 0.0f)                      // nextColor (r, g, b)
    // );
    // MyVertex topRight(
    //     MyVec3(0.1f + offset, 0.1f + offset, 0.0f),   // position (x, y, z)
    //     MyVec3(0.1f + offset, 0.1f + offset, 0.0f),   // nextPosition (x, y, z)
    //     MyVec3(0.0f, 1.0f, 0.0f),                     // color (r, g, b)
    //     MyVec3(0.0f, 0.0f, 1.0f)                      // nextColor (r, g, b)
    // );
    // MyVertex bottomRight(
    //     MyVec3(0.1f + offset, -0.1f + offset, 0.0f),  // position (x, y, z)
    //     MyVec3(0.1f + offset, -0.1f + offset, 0.0f),  // nextPosition (x, y, z)
    //     MyVec3(0.0f, 0.0f, 1.0f),                     // color (r, g, b)
    //     MyVec3(0.0f, 1.0f, 0.0f)                      // nextColor (r, g, b)
    // );
    // MyVertex bottomLeft(
    //     MyVec3(-0.1f + offset, -0.1f + offset, 0.0f), // position (x, y, z)
    //     MyVec3(-0.1f + offset, -0.1f + offset, 0.0f), // nextPosition (x, y, z)
    //     MyVec3(1.0f, 1.0f, 0.0f),                     // color (r, g, b)
    //     MyVec3(0.0f, 0.0f, 1.0f)                      // nextColor (r, g, b)
    // );
    // MyQuad quadC(topLeft, topRight, bottomRight, bottomLeft);

    // MyVertex vertices[100];
    // int i = 0;
    // for (MyVertex vertex : quadA.GetVertices()) {
    //     vertices[i] = vertex;
    //     i++;
    // }
    // for (MyVertex vertex : quadB.GetVertices()) {
    //     vertices[i] = vertex;
    //     i++;
    // }
    // for (MyVertex vertex : quadC.GetVertices()) {
    //     vertices[i] = vertex;
    //     i++;
    // }

     //* Rainbow Cube
    MyVertex vertices[] = {
        MyVertex(
           -0.5f,  -0.5f, -0.5f, // position
            1.0f,  0.0f, 0.0f,   // color
            1.0f,  0.0f, 0.0f    // nextColor
        ), // Bottom-left-back
        MyVertex(
            -0.5f,  0.5f, -0.5f, // position
            0.0f,  1.0f, 0.0f,   // color
            0.0f,  1.0f, 0.0f    // nextColor
        ), // Top-left-back
        MyVertex(
            0.5f,  0.5f, -0.5f, // position
            0.0f,  0.0f, 1.0f, // color
            0.0f,  0.0f, 1.0f  // nextColor
        ), // Top-right-front
        MyVertex(
            0.5f,  -0.5f, -0.5f, // position
            1.0f,  1.0f, 0.0f,   // color
            1.0f,  1.0f, 0.0f    // nextColor
        ), // Bottom-right-back
        MyVertex(
            0.5f, -0.5f, 0.5f,  // position
            1.0f,  0.0f, 1.0f,  // color
            1.0f,  0.0f, 1.0f   // nextColor
        ), // Bottom-right-front
        MyVertex(
            0.5f,  0.5f, 0.5f,  // position
            0.0f,  1.0f, 1.0f,  // color
            0.0f,  1.0f, 1.0f   // nextColor
        ), // Top-right-front
        MyVertex(
            -0.5f,  0.5f, 0.5f, // position
            1.0f,  1.0f, 1.0f,  // color
            1.0f,  1.0f, 1.0f   // nextColor
        ), // Top-left-front
        MyVertex(
            -0.5f,  -0.5f, 0.5f, // position
            0.0f,  0.0f, 0.0f,   // color
            0.0f,  0.0f, 0.0f    // nextColor
        ), // Bottom-left-front
    };

    unsigned int indices[] = {
        //* FRONT
        0, 1, 2,
        2, 3, 0,
        //* BACK
        4, 5, 6,
        6, 7, 4,
        //* TOP
        1, 6, 5,
        5, 2, 1,
        //* BOTTOM
        7, 0, 3,
        3, 4, 7,
        //* RIGHT
        3, 2, 5,
        5, 4, 3,
        //* LEFT
        7, 6, 1,
        1, 0, 7,
    };
    this->indexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateIndexBuffer(indices, ARRAYSIZE(indices));
    if (!this->indexBuffer) {
        std::cerr << "[ERROR] Failed to create indexBuffer!" << std::endl;
        throw std::exception("Failed to create indexBuffer!");
        return;
    }

    // Compile and create vertex shader
    void* vertexShaderByteCode = nullptr;
    size_t vertexShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileVertexShader(
        VERTEX_SHADER_DIRECTORY.c_str(), "main", &vertexShaderByteCode, &vertexShaderSize)) {
        throw std::exception("Failed to compile vertex shader!");
        return;
    }
    this->vertexShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexShader(vertexShaderByteCode, vertexShaderSize);
    if (!this->vertexShader) {
        throw std::exception("Failed to create vertexShader!");
        return;
    }

    this->vertexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexBuffer(vertices, sizeof(MyVertex), ARRAYSIZE(vertices), vertexShaderByteCode, vertexShaderSize);
    if (!this->vertexBuffer) {
        throw std::exception("Failed to create vertexBuffer!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    // Compile and create pixel shader
    void* pixelShaderByteCode = nullptr;
    size_t pixelShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompilePixelShader(
        PIXEL_SHADER_DIRECTORY.c_str(), "main", &pixelShaderByteCode, &pixelShaderSize)) {
        throw std::exception("Failed to compile pixel shader!");
        return;
    }
    this->pixelShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreatePixelShader(pixelShaderByteCode, pixelShaderSize);
    if (!this->pixelShader) {
        throw std::exception("Failed to create pixelShader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    if (LOG_INFO_CONSTANT_BUFFER) std::cout << "[INFO] : Setting constant buffer" << std::endl;
    this->constantData.time = 0;
    this->constantData.world.Translate(MyVec3(0.0f, 0.0f, 0.0f));
    this->constantData.view.SetIdentity();

    //* Set Projection Matrix
    this->constantData.projection.SetOrthographicLeftHand(
        (this->GetWindowRect().right - this->GetWindowRect().left) / 200.0f,
        (this->GetWindowRect().bottom - this->GetWindowRect().top) / 200.0f,
        -4.0f,
        4.0
    );
    this->constantData.projection.SetPerspectiveLeftHand(
        45.0f * 3.14159265f / 180.0f, // FOV in radians
        (this->GetWindowRect().right - this->GetWindowRect().left) / (float)(this->GetWindowRect().bottom - this->GetWindowRect().top),
        0.1f, // Near plane
        100.0f // Far plane
    );
    this->constantBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateConstantBuffer(&constantData, sizeof(MyConstant));
    if (!this->constantBuffer) {
        throw std::exception("Failed to create constantBuffer!");
        return;
    }
}

void MyAppWindow::OnUpdate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnUpdate called" << std::endl;

    MyWindow::OnUpdate();
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : OnUpdate called" << std::endl;
    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : Updating input system in MyAppWindow::OnUpdate" << std::endl;
    MyInputSystem::GetInstance()->Update();
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : OnUpdate called" << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->ClearRenderTargetColor(this->swapChain, MyVec4(0.0f, 0.3f, 0.4f, 1.0f));

    RECT windowRectangle = this->GetWindowRect();
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetViewPortSize(windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top);


    this->UpdateObjects();

    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);

    // Set shaders before drawing
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Setting vertex and pixel shaders" << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetVertexShader(this->vertexShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetPixelShader(this->pixelShader);

    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Setting vertex buffer: " << this->vertexBuffer << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Setting index buffer: " << this->indexBuffer << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->SetIndexBuffer(this->indexBuffer);

    // Draw non-indexed
    // MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->DrawTriangles(this->vertexBuffer->GetVertexCount(), 0);
    // Draw indexed
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmedieateDeviceContext()->DrawIndexedTriangles(this->indexBuffer->GetIndexCount(), 0, 0);

    if (this->swapChain) {
        if (LOG_INFO_WINDOW) std::cout << "[INFO] : Presenting swap chain" << std::endl;
        this->swapChain->Present(true);
    }

    this->UpdateDeltaTime();
}

void MyAppWindow::OnDestroy() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnDestroy called" << std::endl;

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : Removing MyAppWindow as input listener" << std::endl;
    MyInputSystem::GetInstance()->RemoveListener(this);

    MyWindow::OnDestroy();
    if (this->vertexBuffer) {
        delete this->vertexBuffer;
        this->vertexBuffer = nullptr;
    }
    if (this->indexBuffer) {
        delete this->indexBuffer;
        this->indexBuffer = nullptr;
    }
    if (this->constantBuffer) {
        delete this->constantBuffer;
        this->constantBuffer = nullptr;
    }
    if (this->vertexShader) {
        delete this->vertexShader;
        this->vertexShader = nullptr;
    }
    if (this->pixelShader) {
        delete this->pixelShader;
        this->pixelShader = nullptr;
    }
    if (this->swapChain) {
        delete this->swapChain;
        this->swapChain = nullptr;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->Release();
}
void MyAppWindow::OnSetFocus() {
    MyInputSystem::GetInstance()->AddListener(this);
}
void MyAppWindow::OnKillFocus() {
    MyInputSystem::GetInstance()->RemoveListener(this);
}

void MyAppWindow::OnKeyDown(int keyCode) {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : W pressed, xRotation increased" << std::endl;
        break;
    case 'A':
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : A pressed, yRotation decreased" << std::endl;
        break;
    case 'S':
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : S pressed, xRotation decreased" << std::endl;
        break;
    case 'D':
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : D pressed, yRotation increased" << std::endl;
        break;
    default:
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO] : Unhandled key down: " << keyCode << std::endl;
        break;
    }
}
void MyAppWindow::OnKeyHold(int keyCode) {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        // this->cameraPosition.z += moveSpeed * this->deltaTime; // Move camera forward
        this->cameraMoveInput.y = 1.0f; // Move camera forward
        break;
    case 'A':
        // this->cameraPosition.x -= moveSpeed * this->deltaTime; // Move camera left
        this->cameraMoveInput.x = -1.0f; // Move camera left
        break;
    case 'S':
        // this->cameraPosition.z -= moveSpeed * this->deltaTime; // Move camera backward
        this->cameraMoveInput.y = -1.0f; // Move camera backward
        break;
    case 'D':
        // this->cameraPosition.x += moveSpeed * this->deltaTime; // Move camera right
        this->cameraMoveInput.x = 1.0f; // Move camera right
        break;
    case 'Q':
        // this->cameraPosition.y += moveSpeed * this->deltaTime; // Move camera up
        this->cameraMoveInput.z = 1.0f; // Move camera up
        break;
    case 'E':
        // this->cameraPosition.y -= moveSpeed * this->deltaTime; // Move camera down
        this->cameraMoveInput.z = -1.0f; // Move camera down
        break;
    default:
        break;
    }
}

void MyAppWindow::OnKeyUp(int keyCode) {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnKeyUp called with keyCode: " << keyCode << std::endl;

    // Handle key up events here
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyAppWindow::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        this->cameraMoveInput.y = 0.0f;
        break;
    case 'A':
        this->cameraMoveInput.x = 0.0f;
        break;
    case 'S':
        this->cameraMoveInput.y = 0.0f;
        break;
    case 'D':
        this->cameraMoveInput.x = 0.0f;
        break;
    case 'Q':
        this->cameraMoveInput.z = 0.0f;
        break;
    case 'E':
        this->cameraMoveInput.z = 0.0f;
        break;
    default:
        break;
    }
}

void MyAppWindow::OnMouseMove(const MyScreenPoint& deltaMousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO] : MyAppWindow::OnMouseMove called with deltaMousePosition: ("
        << deltaMousePosition.x << ", " << deltaMousePosition.y << ")" << std::endl;

    // this->xRotation += deltaMousePosition.y * this->rotationSpeed * this->deltaTime;
    // this->yRotation += deltaMousePosition.x * this->rotationSpeed * this->deltaTime;

    if (this->lockMouse)
        MyInputSystem::GetInstance()->SetCursorPosition(
            MyScreenPoint(
                (this->GetWindowRect().right - this->GetWindowRect().left) / 2,
                (this->GetWindowRect().bottom - this->GetWindowRect().top) / 2
            )
        );
}

void MyAppWindow::OnLMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO] : MyAppWindow::OnLMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}
void MyAppWindow::OnLMBHold(const MyScreenPoint& deltaMousePosition) {
    this->cameraRotation.x += (float)((deltaMousePosition.y - (this->GetWindowRect().bottom - this->GetWindowRect().top) / 2.0f) * this->rotationSpeed * this->deltaTime);
}
void MyAppWindow::OnLMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO] : MyAppWindow::OnLMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}
void MyAppWindow::OnRMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO] : MyAppWindow::OnRMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}
void MyAppWindow::OnRMBHold(const MyScreenPoint& deltaMousePosition) {
    this->cameraRotation.y += (float)((deltaMousePosition.x - ((this->GetWindowRect().right - this->GetWindowRect().left) / 2.0)) * this->rotationSpeed * this->deltaTime);
}
void MyAppWindow::OnRMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO] : MyAppWindow::OnRMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}