#include "Window/MyAppWindow.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;
extern bool LOG_INFO_WINDOW_UPDATE;
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
extern const std::wstring IMGUI_LOGO_DIRECTORY;

static ImVec4 myColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Default: Red
static bool freeMouse = false; // Toggle for mouse/camera control
static void* imguiLogoSRV = nullptr; // Holds the logo texture SRV

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
    this->globalConstantData.time = 0;
    this->globalConstantData.world.Translate(MyVector3(0.0f, 0.0f, 0.0f));
    this->globalConstantData.world.Scale(MyVector3(1.0f, 1.0f, 1.0f));
    this->globalConstantData.world.Rotate(MyVector3(0.0f, 0.0f, 0.0f));
    this->globalConstantData.view.SetIdentity();
    this->globalConstantData.projection = this->activeCamera->projectionMatrix;
    this->globalConstantBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateConstantBuffer(&globalConstantData, sizeof(MyConstant));
    if (!this->globalConstantBuffer) {
        throw std::exception("Failed to create constantBuffer!");
        return;
    }
}

void MyAppWindow::DebugLaunchFunction() {
    //!! Experimental
    //* Texture Application
    this->sampleTexture = MyGraphicsEngine::GetInstance()->GetTextureManager()->CreateTextureFromFile(SAMPLE_TEXTURE_DIRECTORY.c_str());
    //* Mesh Application
    this->meshes.push_back(MyGraphicsEngine::GetInstance()->GetMeshManager()->CreateUniqueMeshFromFile(SAMPLE_MESH_DIRECTORY.c_str()));
    this->meshes.push_back(MyGraphicsEngine::GetInstance()->GetMeshManager()->CreateUniqueMeshFromFile(SAMPLE_MESH_DIRECTORY.c_str()));
    this->meshes.push_back(MyGraphicsEngine::GetInstance()->GetMeshManager()->CreateUniqueMeshFromFile(SAMPLE_MESH_DIRECTORY.c_str()));

    this->meshes[0]->time = 0.0f;
    this->meshes[1]->time = 2.0f;
    this->meshes[2]->time = 4.0f;
}

void MyAppWindow::ImGuiUpdate() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: ImGui Update..." << std::endl;

    // Start ImGui frame (should already be in your render loop)
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static bool showCredits = false;
    static bool showColorPickerUI = false;
    // freeMouse is now file-static

    // Menu Bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("Credits")) {
                showCredits = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("UI")) {
            if (ImGui::MenuItem("Color Picker")) {
                showColorPickerUI = true;
            }
            ImGui::MenuItem("Free Mouse", nullptr, &freeMouse);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Handle mouse/camera toggle
    static bool prevFreeMouse = false;
    if (freeMouse != prevFreeMouse) {
        MyInputSystem::GetInstance()->SetCursorVisibility(freeMouse);
        MyInputSystem::GetInstance()->lockMouse = !freeMouse;
        prevFreeMouse = freeMouse;
    }

    // Credits Modal
    if (showCredits) {
        ImGui::OpenPopup("Credits");
    }
    // Load logo texture once
    if (!imguiLogoSRV && !IMGUI_LOGO_DIRECTORY.empty()) {
        auto tex = MyGraphicsEngine::GetInstance()->GetTextureManager()->CreateTextureFromFile(IMGUI_LOGO_DIRECTORY.c_str());
        if (tex) imguiLogoSRV = tex->GetShaderResourceView();
    }

    if (ImGui::BeginPopupModal("Credits", &showCredits, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        if (imguiLogoSRV) {
            ImGui::Image(imguiLogoSRV, ImVec2(128, 128));
        }
        else {
            ImGui::Button("DLSU Logo", ImVec2(128, 128));
        }
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Text("De La Salle University");
        ImGui::Text(" ");
        ImGui::Text("Developer: Conrad Ubay");
        ImGui::Text(" ");
        ImGui::Text("Acknowledgments:");
        ImGui::BulletText("Sir Neil Patrick Delgallego's GDEND03 Course");
        ImGui::BulletText("Mostly inspired by Pardcode's playlist \"Game Engine Tutorial Series\" on YouTube");
        if (ImGui::Button("Close")) {
            showCredits = false;
            ImGui::CloseCurrentPopup();
        }


        ImGui::EndPopup();
    }

    // Color Picker Placeholder UI
    if (showColorPickerUI) {
        ImGui::Begin("Color Picker UI", &showColorPickerUI);
        ImGui::Text("Color Picker Placeholder");
        ImGui::ColorPicker4("Color Wheel", (float*)&myColor);
        ImGui::End();
    }

    // Render ImGui
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void MyAppWindow::UpdateDeltaTime() {
    this->oldTime = this->newTime;
    this->newTime = ::GetTickCount64();
    this->deltaTime = this->oldTime ? (this->newTime - this->oldTime) / 1000.0f : 0.0f;
    this->globalConstantData.time += this->deltaTime;
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Updating deltaTime... Lifetime(" << this->globalConstantData.time << "), deltaTime(" << this->deltaTime << ")" << std::endl;
}

void MyAppWindow::UpdateObjects() {
    for (MyMeshPtr mesh : this->meshes)
        mesh->Update(this->deltaTime);

    //* Update Active Camera
    this->activeCamera->Update(this->deltaTime);
    this->globalConstantData.view = this->activeCamera->transform->worldMatrix;
}

void MyAppWindow::UpdateConstantBuffer() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Updating constant buffer..." << std::endl;
    this->globalConstantBuffer->Update(MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext(), &this->globalConstantData);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->globalConstantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->hullShader, this->globalConstantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->domainShader, this->globalConstantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->globalConstantBuffer);
}

void MyAppWindow::UpdateShaders() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Updating shaders..." << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetHullShader(this->hullShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetDomainShader(this->domainShader);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);
}

void MyAppWindow::DrawLoop() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Drawing meshes..." << std::endl;
    for (MyMeshPtr mesh : this->meshes)
        mesh->Draw(this->vertexShader, this->hullShader, this->domainShader, this->pixelShader,
            this->activeCamera->transform->worldMatrix, this->activeCamera->projectionMatrix, this->globalConstantData.time);
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

    //* Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Initialize ImGui for Win32 + DX11
    ImGui_ImplWin32_Init(this->windowHandle);
    ImGui_ImplDX11_Init(
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetD3DDevice(),
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->GetD3DDeviceContext()
    );

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
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: MyAppWindow::OnUpdate called" << std::endl;

    MyWindow::OnUpdate();
    MyInputSystem::GetInstance()->Update();
    this->UpdateObjects();

    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, MyVector4(0.3f, 0.3f, 0.3f, 1.0f));
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetViewPortSize(this->width, this->height);


    this->UpdateConstantBuffer();
    this->UpdateShaders();
    // Set texture for pixel shader
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Setting texture: " << this->sampleTexture << std::endl;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetTexture(this->pixelShader, this->sampleTexture);

    // Set sampler state for pixel shader
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetSamplerState();

    this->DrawLoop();

    this->ImGuiUpdate();
    if (this->swapChain) {
        if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Presenting swap chain" << std::endl;
        this->swapChain->Present(true);
    }

    this->UpdateDeltaTime();
}

void MyAppWindow::OnDestroy() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnDestroy called" << std::endl;

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Removing MyAppWindow as input listener" << std::endl;
    MyInputSystem::GetInstance()->RemoveListener(this);

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    MyWindow::OnDestroy();
    this->vertexBuffer = nullptr;
    this->indexBuffer = nullptr;
    this->globalConstantBuffer = nullptr;
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
    case 'L':
        freeMouse = !freeMouse;
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