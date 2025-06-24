#include "Window/MyAppWindow.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;
extern bool LOG_INFO_CONSTANT_BUFFER;
extern bool LOG_INFO_INPUT_SYSTEM_KEYBOARD;
extern bool LOG_INFO_INPUT_SYSTEM_MOUSE;
// Add extern declarations for shader path constants
extern const std::wstring HULL_SHADER_DIRECTORY;
extern const std::wstring DOMAIN_SHADER_DIRECTORY;
extern const std::wstring VERTEX_SHADER_DIRECTORY;
extern const std::wstring PIXEL_SHADER_DIRECTORY;
extern const std::wstring SAMPLE_TEXTURE_DIRECTORY;
extern const std::wstring SAMPLE_MESH_DIRECTORY;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyAppWindow::MyAppWindow() {}
MyAppWindow::~MyAppWindow() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyAppWindow::InitializeShaders() {
    //* Vertex Shader Application
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
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    //* Hull Shader Application
    void* hullShaderByteCode = nullptr;
    size_t hullShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileHullShader(
        HULL_SHADER_DIRECTORY.c_str(), "main", &hullShaderByteCode, &hullShaderSize)) {
        throw std::exception("Failed to compile hull shader!");
        return;
    }
    this->hullShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateHullShader(hullShaderByteCode, hullShaderSize);
    if (!this->hullShader) {
        throw std::exception("Failed to create hullShader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    //* Domain Shader Application
    void* domainShaderByteCode = nullptr;
    size_t domainShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileDomainShader(
        DOMAIN_SHADER_DIRECTORY.c_str(), "main", &domainShaderByteCode, &domainShaderSize)) {
        throw std::exception("Failed to compile domain shader!");
        return;
    }
    this->domainShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateDomainShader(domainShaderByteCode, domainShaderSize);
    if (!this->domainShader) {
        throw std::exception("Failed to create domainShader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    //* Pixel Shader Application
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

}

void MyAppWindow::InitializeConstantData() {
    if (LOG_INFO_CONSTANT_BUFFER) std::cout << "[INFO]: Setting constant buffer" << std::endl;
    this->constantData.time = 0;
    this->constantData.world.Translate(MyVector3(0.0f, 0.0f, 0.0f));
    this->constantData.world.Scale(MyVector3(1.0f, 1.0f, 1.0f));
    this->constantData.world.Rotate(MyVector3(0.0f, 0.0f, 0.0f));
    this->constantData.view.SetIdentity();
    this->constantData.projection = this->activeCamera->projectionMatrix;
    this->constantBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateConstantBuffer(&constantData, sizeof(MyConstant));
    if (!this->constantBuffer) {
        throw std::exception("Failed to create constantBuffer!");
        return;
    }
}

void MyAppWindow::DebugLaunchFunction() {
    //!! Experimental
    //* Texture Application
    this->sampleTexture = MyGraphicsEngine::GetInstance()->GetTextureManager()->CreateTextureFromFile(SAMPLE_TEXTURE_DIRECTORY.c_str());
    //* Mesh Application
    this->meshes.push_back(MyGraphicsEngine::GetInstance()->GetMeshManager()->CreateMeshFromFile(SAMPLE_MESH_DIRECTORY.c_str()));
}

void MyAppWindow::UpdateDeltaTime() {
    this->oldTime = this->newTime;
    this->newTime = ::GetTickCount64();
    this->deltaTime = this->oldTime ? (this->newTime - this->oldTime) / 1000.0f : 0.0f;
    this->constantData.time += this->deltaTime;
}

void MyAppWindow::UpdateObjects() {
    for (MyMeshPtr mesh : this->meshes)
        mesh->Update(this->deltaTime);

    //* Update Active Camera
    this->activeCamera->Update(this->deltaTime);
    this->constantData.view = this->activeCamera->transform->worldMatrix;
}

void MyAppWindow::UpdateConstantBuffer() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: Updating constant buffer..." << std::endl;
    this->constantBuffer->Update(MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext(), &this->constantData);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->hullShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->domainShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);
}

void MyAppWindow::UpdateShaders() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: Updating shaders..." << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetHullShader(this->hullShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetDomainShader(this->domainShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyAppWindow::OnCreate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnCreate called" << std::endl;

    MyWindow::OnCreate();

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Registering MyAppWindow as input listener" << std::endl;
    MyInputSystem::GetInstance()->windowWidth = this->width;
    MyInputSystem::GetInstance()->windowHeight = this->height;

    MyInputSystem::GetInstance()->AddListener(this);
    MyInputSystem::GetInstance()->SetCursorVisibility(false);

    //* Create First Camera
    try {
        this->cameras.push_back(std::make_shared<MyCamera>());
        // this->activeCamera->SetOrthographicLeftHand(
        //     this->width / 200.0f,
        //     this->height / 200.0f,
        //     -4.0f,
        //     4.0
        // );
        this->cameras[0]->SetPerspectiveLeftHand(
            45.0f * 3.14159265f / 180.0f, // FOV in radians
            this->width / (float)this->height,
            0.00001f, // Near plane
            10000.0f // Far plane
        );
        this->activeCamera = this->cameras[0];
        if (!this->activeCamera) {
            std::cerr << "[ERROR]: Failed to create camera in MyAppWindow::OnCreate" << std::endl;
            throw std::exception("Failed to create camera in MyAppWindow::OnCreate");
        }
        MyInputSystem::GetInstance()->AddListener(this->activeCamera.get());
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in MyAppWindow::OnCreate: " << ex.what() << std::endl;
    }

    //* Create Swapchain
    swapChain = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateSwapChain(this->windowHandle, this->width, this->height);
    this->InitializeShaders();
    this->InitializeConstantData();
    this->DebugLaunchFunction();
}

void MyAppWindow::OnUpdate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnUpdate called" << std::endl;

    MyWindow::OnUpdate();
    MyInputSystem::GetInstance()->Update();
    this->UpdateObjects();
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: OnUpdate called" << std::endl;

    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, MyVector4(0.3f, 0.3f, 0.3f, 1.0f));
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetViewPortSize(this->width, this->height);
    this->UpdateConstantBuffer();
    this->UpdateShaders();
    // Set texture for pixel shader
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: Setting texture: " << this->sampleTexture << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetTexture(this->pixelShader, this->sampleTexture);

    // Set sampler state for pixel shader
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetSamplerState();

    for (MyMeshPtr mesh : this->meshes)
        mesh->Draw();

    if (this->swapChain) {
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: Presenting swap chain" << std::endl;
        this->swapChain->Present(true);
    }

    this->UpdateDeltaTime();
}

void MyAppWindow::OnDestroy() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnDestroy called" << std::endl;

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Removing MyAppWindow as input listener" << std::endl;
    MyInputSystem::GetInstance()->RemoveListener(this);

    MyWindow::OnDestroy();
    this->vertexBuffer = nullptr;
    this->indexBuffer = nullptr;
    this->constantBuffer = nullptr;
    this->hullShader = nullptr;
    this->domainShader = nullptr;
    this->vertexShader = nullptr;
    this->pixelShader = nullptr;
    this->swapChain = nullptr;
}

void MyAppWindow::OnSetFocus() {
    MyInputSystem::GetInstance()->lockMouse = true;
    MyInputSystem::GetInstance()->AddListener(this);
    MyInputSystem::GetInstance()->AddListener(this->activeCamera.get());
}

void MyAppWindow::OnKillFocus() {
    MyInputSystem::GetInstance()->lockMouse = false;
    MyInputSystem::GetInstance()->RemoveListener(this);
    MyInputSystem::GetInstance()->RemoveListener(this->activeCamera.get());
}

void MyAppWindow::OnKeyDown(int keyCode) {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'M':
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: M pressed, wireframe mode enabled" << std::endl;
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->ToggleWireframeMode(true);
        break;
    case 'N':
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: N pressed, wireframe mode disabled" << std::endl;
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->ToggleWireframeMode(false);
        break;
    default:
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Unhandled key down: " << keyCode << std::endl;
        break;
    }
}

void MyAppWindow::OnKeyHold(int keyCode) {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        break;
    case 'A':
        break;
    case 'S':
        break;
    case 'D':
        break;
    case 'Q':
        break;
    case 'E':
        break;
    default:
        break;
    }
}

void MyAppWindow::OnKeyUp(int keyCode) {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnKeyUp called with keyCode: " << keyCode << std::endl;

    // Handle key up events here
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        break;
    case 'A':
        break;
    case 'S':
        break;
    case 'D':
        break;
    case 'Q':
        break;
    case 'E':
        break;
    default:
        break;
    }
}

void MyAppWindow::OnMouseMove(const MyVector2& deltaMousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE && false) std::cout << "[INFO]: MyAppWindow::OnMouseMove called with deltaMousePosition: ("
        << deltaMousePosition.x << ", " << deltaMousePosition.y << ")" << std::endl;
}

void MyAppWindow::OnLMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE && false) std::cout << "[INFO]: MyAppWindow::OnLMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyAppWindow::OnLMBHold(const MyVector2& deltaMousePosition) {
}

void MyAppWindow::OnLMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE && false) std::cout << "[INFO]: MyAppWindow::OnLMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyAppWindow::OnRMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE && false) std::cout << "[INFO]: MyAppWindow::OnRMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyAppWindow::OnRMBHold(const MyVector2& deltaMousePosition) {
}

void MyAppWindow::OnRMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE && false) std::cout << "[INFO]: MyAppWindow::OnRMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}