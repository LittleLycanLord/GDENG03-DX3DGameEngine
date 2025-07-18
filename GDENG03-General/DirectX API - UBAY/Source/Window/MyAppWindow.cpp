#include "Window/MyAppWindow.hpp"
#include "Core/MyLogger.hpp"
#include <windows.h>  // For VK_ESCAPE and other virtual key codes

using namespace DX3D;
// Add extern declarations for shader path constants
extern const std::wstring HULL_SHADER_DIRECTORY;
extern const std::wstring DOMAIN_SHADER_DIRECTORY;
extern const std::wstring VERTEX_SHADER_DIRECTORY;
extern const std::wstring PIXEL_SHADER_DIRECTORY;
extern const std::wstring LIGHTING_VERTEX_SHADER_DIRECTORY;
extern const std::wstring LIGHTING_PIXEL_SHADER_DIRECTORY;
extern const std::wstring LIGHTING_HULL_SHADER_DIRECTORY;
extern const std::wstring LIGHTING_DOMAIN_SHADER_DIRECTORY;
extern const std::wstring SAMPLE_TEXTURE_DIRECTORY;
extern const std::wstring SAMPLE_MESH_DIRECTORY;
extern const std::wstring IMGUI_LOGO_DIRECTORY;

static ImVec4 myColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Default: Red
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
    PERFORMANCE_TIMER("WINDOW", "InitializeShaders");
    LOG_INFO("SHADERS", "Starting shader compilation and initialization");

    //* Vertex Shader Application
    LOG_DEBUG("SHADERS", "Compiling vertex shader");
    void* vertexShaderByteCode = nullptr;
    size_t vertexShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileVertexShader(
        VERTEX_SHADER_DIRECTORY.c_str(), "main", &vertexShaderByteCode, &vertexShaderSize)) {
        LOG_ERROR("SHADERS", "Failed to compile vertex shader!");
        throw std::exception("Failed to compile vertex shader!");
        return;
    }
    LOG_INFO("SHADERS", "Vertex shader compiled successfully");

    this->vertexShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexShader(vertexShaderByteCode, vertexShaderSize);
    if (!this->vertexShader) {
        LOG_ERROR("SHADERS", "Failed to create vertex shader object!");
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

void MyAppWindow::InitializeLightingShaders() {
    PERFORMANCE_TIMER("WINDOW", "InitializeLightingShaders");
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Starting lighting shader compilation and initialization" << std::endl;

    //* Lighting Vertex Shader
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Compiling lighting vertex shader" << std::endl;
    void* lightingVertexShaderByteCode = nullptr;
    size_t lightingVertexShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileVertexShader(
        LIGHTING_VERTEX_SHADER_DIRECTORY.c_str(), "main", &lightingVertexShaderByteCode, &lightingVertexShaderSize)) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to compile lighting vertex shader!" << std::endl;
        throw std::exception("Failed to compile lighting vertex shader!");
        return;
    }
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Lighting vertex shader compiled successfully" << std::endl;

    this->lightingVertexShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexShader(lightingVertexShaderByteCode, lightingVertexShaderSize);
    if (!this->lightingVertexShader) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to create lighting vertex shader object!" << std::endl;
        throw std::exception("Failed to create lighting vertex shader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    //* Lighting Pixel Shader
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Compiling lighting pixel shader" << std::endl;
    void* lightingPixelShaderByteCode = nullptr;
    size_t lightingPixelShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompilePixelShader(
        LIGHTING_PIXEL_SHADER_DIRECTORY.c_str(), "main", &lightingPixelShaderByteCode, &lightingPixelShaderSize)) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to compile lighting pixel shader!" << std::endl;
        throw std::exception("Failed to compile lighting pixel shader!");
        return;
    }
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Lighting pixel shader compiled successfully" << std::endl;

    this->lightingPixelShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreatePixelShader(lightingPixelShaderByteCode, lightingPixelShaderSize);
    if (!this->lightingPixelShader) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to create lighting pixel shader object!" << std::endl;
        throw std::exception("Failed to create lighting pixel shader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    //* Lighting Hull Shader
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Compiling lighting hull shader" << std::endl;
    void* lightingHullShaderByteCode = nullptr;
    size_t lightingHullShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileHullShader(
        LIGHTING_HULL_SHADER_DIRECTORY.c_str(), "main", &lightingHullShaderByteCode, &lightingHullShaderSize)) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to compile lighting hull shader!" << std::endl;
        throw std::exception("Failed to compile lighting hull shader!");
        return;
    }

    this->lightingHullShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateHullShader(lightingHullShaderByteCode, lightingHullShaderSize);
    if (!this->lightingHullShader) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to create lighting hull shader object!" << std::endl;
        throw std::exception("Failed to create lighting hull shader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();

    //* Lighting Domain Shader
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Compiling lighting domain shader" << std::endl;
    void* lightingDomainShaderByteCode = nullptr;
    size_t lightingDomainShaderSize = 0;
    if (!MyGraphicsEngine::GetInstance()->GetRenderSystem()->CompileDomainShader(
        LIGHTING_DOMAIN_SHADER_DIRECTORY.c_str(), "main", &lightingDomainShaderByteCode, &lightingDomainShaderSize)) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to compile lighting domain shader!" << std::endl;
        throw std::exception("Failed to compile lighting domain shader!");
        return;
    }

    this->lightingDomainShader = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateDomainShader(lightingDomainShaderByteCode, lightingDomainShaderSize);
    if (!this->lightingDomainShader) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to create lighting domain shader object!" << std::endl;
        throw std::exception("Failed to create lighting domain shader!");
        return;
    }
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->ReleaseCompiledShader();
    
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Lighting shaders initialized successfully" << std::endl;
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

    // this->meshes[0]->lifetime = 0.0f;
    // this->meshes[1]->lifetime = 2.0f;
    // this->meshes[2]->lifetime = 4.0f;

    // Position meshes in a row for lighting testing
    this->meshes[0]->transform->position = MyVector3(-3.0f, 0.0f, 0.0f);  // Left
    this->meshes[1]->transform->position = MyVector3(0.0f, 0.0f, 0.0f);   // Center
    this->meshes[2]->transform->position = MyVector3(3.0f, 0.0f, 0.0f);   // Right
    
    // Set uniform scale for all meshes
    this->meshes[0]->transform->scale = MyVector3(0.1f);
    this->meshes[1]->transform->scale = MyVector3(0.1f);
    this->meshes[2]->transform->scale = MyVector3(0.1f);

    // Add sample lights for testing the integrated lighting system
    if (MyLightManager::GetInstance()) {
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Adding sample lights for testing..." << std::endl;

        // Clear existing lights and reset the lighting system
        MyLightManager::GetInstance()->RemoveAllLights();

        // Set up ambient lighting
        MyLightManager::GetInstance()->SetAmbientLight(MyVector3(0.1f, 0.1f, 0.15f), 0.3f);

        // Add a warm directional light (like sunset lighting)
        auto sunLight = MyLightManager::GetInstance()->AddDirectionalLight(
            MyVector3(1.0f, 0.8f, 0.6f), // Warm orange-yellow color
            1.2f // Intensity
        );
        sunLight->transform->rotation = MyVector3(-30.0f, 45.0f, 0.0f); // Angled from above-right

        // Add a bright point light that will move around (animated in UpdateObjects)
        auto movingPointLight = MyLightManager::GetInstance()->AddPointLight(
            MyVector3(0.0f, 3.0f, 0.0f),  // Starting position above center mesh
            MyVector3(0.3f, 0.8f, 1.0f),  // Cool blue color
            4.0f,                         // High intensity
            12.0f                         // Good range
        );

        // Add a stationary red point light on the left
        auto leftPointLight = MyLightManager::GetInstance()->AddPointLight(
            MyVector3(-5.0f, 1.5f, 2.0f), // Left side, elevated
            MyVector3(1.0f, 0.2f, 0.2f),  // Red color
            3.0f,                         // Moderate intensity
            8.0f                          // Medium range
        );

        // Add a green spot light pointing down from above-right
        auto spotLight = MyLightManager::GetInstance()->AddSpotLight(
            MyVector3(4.0f, 4.0f, 3.0f),  // Above and to the right
            MyVector3(0.0f, -1.0f, 0.0f), // Direction pointing down
            MyVector3(0.2f, 1.0f, 0.3f),  // Green color
            2.5f,                         // Intensity
            15.0f                         // Range
        );
        // Point the spot light down and slightly toward center
        spotLight->transform->rotation = MyVector3(-45.0f, -30.0f, 0.0f);

        // Add a purple point light on the right
        auto rightPointLight = MyLightManager::GetInstance()->AddPointLight(
            MyVector3(5.0f, 1.0f, -2.0f), // Right side
            MyVector3(0.8f, 0.3f, 1.0f),  // Purple color
            2.8f,                         // Intensity
            10.0f                         // Range
        );

        if (LOG_INFO_LIGHTING) {
            std::cout << "[INFO]: Added " << MyLightManager::GetInstance()->GetLightCount() << " sample lights:" << std::endl;
            std::cout << "  - 1 Directional light (warm sunset)" << std::endl;
            std::cout << "  - 3 Point lights (blue/moving, red/left, purple/right)" << std::endl;
            std::cout << "  - 1 Spot light (green, pointing down)" << std::endl;
            std::cout << "[INFO]: Use '1' key to toggle between standard and lighting shaders" << std::endl;
        }
    }
}

void MyAppWindow::ImGuiUpdate() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: ImGui Update..." << std::endl;

    // Start ImGui frame (should already be in your render loop)
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static bool showCredits = false;
    static bool showColorPickerUI = false;
    static bool showLoggingControls = false;
    static bool showLightingControls = false;
    // this->freeMouse is now file-static

    // Menu Bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("Credits")) {
                showCredits = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug")) {
            if (ImGui::MenuItem("Logging Controls")) {
                showLoggingControls = true;
            }
            if (ImGui::MenuItem("Lighting Controls")) {
                showLightingControls = true;
            }
            ImGui::MenuItem("Free Mouse", nullptr, &this->freeMouse);
            ImGui::MenuItem("Use Lighting Shaders", nullptr, &this->useLightingShaders);
            ImGui::MenuItem("Enable Tessellation", nullptr, &this->useTessellation);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("UI")) {
            if (ImGui::MenuItem("Color Picker")) {
                showColorPickerUI = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // Handle mouse/camera toggle
    static bool prevFreeMouse = false;
    if (this->freeMouse != prevFreeMouse) {
        MyInputSystem::GetInstance()->SetCursorVisibility(this->freeMouse);
        MyInputSystem::GetInstance()->lockMouse = !this->freeMouse;

        // Add/Remove camera from input listeners based on freeMouse state
        if (this->freeMouse) {
            // Mouse is free - remove camera from input listeners so it doesn't receive mouse input
            MyInputSystem::GetInstance()->RemoveListener(this->activeCamera.get());
        }
        else {
            // Mouse is locked - add camera back to input listeners so it can control the view
            MyInputSystem::GetInstance()->AddListener(this->activeCamera.get());
        }

        prevFreeMouse = this->freeMouse;
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

    // Logging Controls Window
    if (showLoggingControls) {
        ImGui::Begin("Engine Logging Controls", &showLoggingControls);
        if (MyLogger::GetInstance()) {
            MyLogger::GetInstance()->RenderImGuiLoggingControls();
        }
        ImGui::End();
    }

    // Lighting Controls Window
    if (showLightingControls) {
        ImGui::Begin("Lighting System Controls", &showLightingControls, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        
        if (MyLightManager::GetInstance()) {
            // Header information
            ImGui::Text("Lighting System Status: Active");
            ImGui::Text("Total Lights: %d", (int)MyLightManager::GetInstance()->GetLightCount());
            ImGui::Text("Lighting Mode: %s", useLightingShaders ? "Enabled" : "Disabled");
            
            // Quick toggle for lighting mode
            if (ImGui::Button(useLightingShaders ? "Disable Lighting" : "Enable Lighting")) {
                useLightingShaders = !useLightingShaders;
            }
            
            ImGui::Separator();
            
            // Global lighting controls
            if (ImGui::CollapsingHeader("Global Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
                // Ambient light controls
                float ambientColor[3] = { 
                    MyLightManager::GetInstance()->GetAmbientLight().x,
                    MyLightManager::GetInstance()->GetAmbientLight().y,
                    MyLightManager::GetInstance()->GetAmbientLight().z
                };
                float ambientIntensity = MyLightManager::GetInstance()->GetAmbientIntensity();
                
                if (ImGui::ColorEdit3("Ambient Color", ambientColor)) {
                    MyLightManager::GetInstance()->SetAmbientLight(
                        MyVector3(ambientColor[0], ambientColor[1], ambientColor[2]), 
                        ambientIntensity
                    );
                }
                if (ImGui::SliderFloat("Ambient Intensity", &ambientIntensity, 0.0f, 2.0f)) {
                    MyLightManager::GetInstance()->SetAmbientLight(
                        MyVector3(ambientColor[0], ambientColor[1], ambientColor[2]), 
                        ambientIntensity
                    );
                }
                
                // Global controls
                ImGui::Spacing();
                if (ImGui::Button("Enable All Lights")) {
                    MyLightManager::GetInstance()->EnableAllLights();
                }
                ImGui::SameLine();
                if (ImGui::Button("Disable All Lights")) {
                    MyLightManager::GetInstance()->DisableAllLights();
                }
                ImGui::SameLine();
                if (ImGui::Button("Remove All Lights")) {
                    MyLightManager::GetInstance()->RemoveAllLights();
                }
            }
            
            ImGui::Separator();
            
            // Light creation controls
            if (ImGui::CollapsingHeader("Add New Lights")) {
                static int lightTypeToAdd = 0;
                const char* lightTypes[] = { "Directional Light", "Point Light", "Spot Light" };
                
                ImGui::Combo("Light Type", &lightTypeToAdd, lightTypes, IM_ARRAYSIZE(lightTypes));
                
                if (ImGui::Button("Add Light")) {
                    MyVector3 defaultColor(1.0f, 1.0f, 1.0f);
                    float defaultIntensity = 1.0f;
                    
                    switch (lightTypeToAdd) {
                        case 0: // Directional Light
                            MyLightManager::GetInstance()->AddDirectionalLight(defaultColor, defaultIntensity);
                            break;
                        case 1: // Point Light
                            MyLightManager::GetInstance()->AddPointLight(MyVector3(0.0f, 2.0f, 0.0f), defaultColor, defaultIntensity, 10.0f);
                            break;
                        case 2: // Spot Light
                            MyLightManager::GetInstance()->AddSpotLight(MyVector3(0.0f, 3.0f, 0.0f), MyVector3(0.0f, -1.0f, 0.0f), defaultColor, defaultIntensity, 15.0f);
                            break;
                    }
                }
            }
            
            ImGui::Separator();
            
            // Individual light controls
            if (ImGui::CollapsingHeader("Individual Lights", ImGuiTreeNodeFlags_DefaultOpen)) {
                // Light statistics
                int directionalCount = 0, pointCount = 0, spotCount = 0;
                for (size_t i = 0; i < MyLightManager::GetInstance()->GetLightCount(); i++) {
                    auto light = MyLightManager::GetInstance()->GetLight(i);
                    if (std::dynamic_pointer_cast<MyDirectionalLight>(light)) directionalCount++;
                    else if (std::dynamic_pointer_cast<MyPointLight>(light)) pointCount++;
                    else if (std::dynamic_pointer_cast<MySpotLight>(light)) spotCount++;
                }
                
                ImGui::Text("Directional: %d | Point: %d | Spot: %d", directionalCount, pointCount, spotCount);
                ImGui::Spacing();
                
                // Individual light controls
                for (size_t i = 0; i < MyLightManager::GetInstance()->GetLightCount(); i++) {
                    auto light = MyLightManager::GetInstance()->GetLight(i);
                    if (!light) continue;
                    
                    ImGui::PushID((int)i);
                    
                    // Determine light type and create appropriate name
                    std::string lightName;
                    std::string lightTypeIcon;
                    
                    if (auto dirLight = std::dynamic_pointer_cast<MyDirectionalLight>(light)) {
                        lightName = "☀️ Directional Light " + std::to_string(i);
                        lightTypeIcon = "☀️";
                    } else if (auto pointLight = std::dynamic_pointer_cast<MyPointLight>(light)) {
                        lightName = "💡 Point Light " + std::to_string(i);
                        lightTypeIcon = "💡";
                    } else if (auto spotLight = std::dynamic_pointer_cast<MySpotLight>(light)) {
                        lightName = "🔦 Spot Light " + std::to_string(i);
                        lightTypeIcon = "🔦";
                    } else {
                        lightName = "❓ Unknown Light " + std::to_string(i);
                        lightTypeIcon = "❓";
                    }
                    
                    // Add enabled/disabled indicator to name
                    if (!light->IsEnabled()) {
                        lightName += " (DISABLED)";
                    }
                    
                    bool headerOpen = ImGui::CollapsingHeader(lightName.c_str());
                    
                    // Quick enable/disable button on same line
                    ImGui::SameLine();
                    bool isEnabled = light->IsEnabled();
                    if (ImGui::Checkbox(("##enabled" + std::to_string(i)).c_str(), &isEnabled)) {
                        light->SetEnabled(isEnabled);
                    }
                    
                    // Quick delete button
                    ImGui::SameLine();
                    if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())) {
                        MyLightManager::GetInstance()->RemoveLight(light);
                        ImGui::PopID();
                        continue; // Skip the rest of this light since it's deleted
                    }
                    
                    if (headerOpen) {
                        ImGui::Indent();
                        
                        // Light type info
                        ImGui::Text("Type: %s", lightTypeIcon.c_str());
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Index: %d", (int)i);
                        
                        // Color control with preview
                        float color[3] = { light->GetColor().x, light->GetColor().y, light->GetColor().z };
                        if (ImGui::ColorEdit3("Color", color)) {
                            light->SetColor(MyVector3(color[0], color[1], color[2]));
                        }
                        
                        // Intensity control with dynamic range
                        float intensity = light->GetIntensity();
                        float maxIntensity = 20.0f; // Adjust based on light type
                        if (auto pointLight = std::dynamic_pointer_cast<MyPointLight>(light)) {
                            maxIntensity = 15.0f;
                        } else if (auto spotLight = std::dynamic_pointer_cast<MySpotLight>(light)) {
                            maxIntensity = 10.0f;
                        }
                        
                        if (ImGui::SliderFloat("Intensity", &intensity, 0.0f, maxIntensity)) {
                            light->SetIntensity(intensity);
                        }
                        
                        // Type-specific controls
                        if (auto dirLight = std::dynamic_pointer_cast<MyDirectionalLight>(light)) {
                            ImGui::Separator();
                            ImGui::Text("Directional Light Properties:");
                            
                            // Direction control via rotation
                            float rotation[3] = { 
                                dirLight->transform->rotation.x,
                                dirLight->transform->rotation.y,
                                dirLight->transform->rotation.z
                            };
                            if (ImGui::SliderFloat3("Rotation", rotation, -180.0f, 180.0f)) {
                                dirLight->transform->rotation = MyVector3(rotation[0], rotation[1], rotation[2]);
                            }
                            
                            // Display calculated direction
                            ImGui::Text("Direction: (%.2f, %.2f, %.2f)", 
                                dirLight->GetDirection().x, 
                                dirLight->GetDirection().y, 
                                dirLight->GetDirection().z);
                        }
                        
                        if (auto pointLight = std::dynamic_pointer_cast<MyPointLight>(light)) {
                            ImGui::Separator();
                            ImGui::Text("Point Light Properties:");
                            
                            // Position control
                            float position[3] = { 
                                pointLight->transform->position.x,
                                pointLight->transform->position.y,
                                pointLight->transform->position.z
                            };
                            if (ImGui::SliderFloat3("Position", position, -20.0f, 20.0f)) {
                                pointLight->transform->position = MyVector3(position[0], position[1], position[2]);
                            }
                            
                            // Range control
                            float range = pointLight->GetRange();
                            if (ImGui::SliderFloat("Range", &range, 0.1f, 50.0f)) {
                                pointLight->SetRange(range);
                            }
                        }
                        
                        if (auto spotLight = std::dynamic_pointer_cast<MySpotLight>(light)) {
                            ImGui::Separator();
                            ImGui::Text("Spot Light Properties:");
                            
                            // Position control
                            float position[3] = { 
                                spotLight->transform->position.x,
                                spotLight->transform->position.y,
                                spotLight->transform->position.z
                            };
                            if (ImGui::SliderFloat3("Position", position, -20.0f, 20.0f)) {
                                spotLight->transform->position = MyVector3(position[0], position[1], position[2]);
                            }
                            
                            // Direction control via rotation
                            float rotation[3] = { 
                                spotLight->transform->rotation.x,
                                spotLight->transform->rotation.y,
                                spotLight->transform->rotation.z
                            };
                            if (ImGui::SliderFloat3("Rotation", rotation, -180.0f, 180.0f)) {
                                spotLight->transform->rotation = MyVector3(rotation[0], rotation[1], rotation[2]);
                            }
                            
                            // Range control
                            float range = spotLight->GetRange();
                            if (ImGui::SliderFloat("Range", &range, 0.1f, 50.0f)) {
                                spotLight->SetRange(range);
                            }
                            
                            // Cone angle controls
                            float innerAngle = spotLight->GetInnerConeAngle();
                            float outerAngle = spotLight->GetOuterConeAngle();
                            
                            if (ImGui::SliderFloat("Inner Cone Angle", &innerAngle, 1.0f, 89.0f)) {
                                // Ensure inner angle is less than outer angle
                                if (innerAngle >= outerAngle) {
                                    outerAngle = innerAngle + 1.0f;
                                    spotLight->SetOuterConeAngle(outerAngle);
                                }
                                spotLight->SetInnerConeAngle(innerAngle);
                            }
                            
                            if (ImGui::SliderFloat("Outer Cone Angle", &outerAngle, 2.0f, 90.0f)) {
                                // Ensure outer angle is greater than inner angle
                                if (outerAngle <= innerAngle) {
                                    innerAngle = outerAngle - 1.0f;
                                    spotLight->SetInnerConeAngle(innerAngle);
                                }
                                spotLight->SetOuterConeAngle(outerAngle);
                            }
                            
                            // Display calculated direction
                            ImGui::Text("Direction: (%.2f, %.2f, %.2f)", 
                                spotLight->GetDirection().x, 
                                spotLight->GetDirection().y, 
                                spotLight->GetDirection().z);
                        }
                        
                        // Animation controls
                        ImGui::Separator();
                        if (ImGui::CollapsingHeader(("Animation##" + std::to_string(i)).c_str())) {
                            ImGui::Text("Animation controls could be added here");
                            ImGui::Text("(e.g., oscillate position, rotate, pulse intensity)");
                        }
                        
                        ImGui::Unindent();
                    }
                    
                    ImGui::PopID();
                }
                
                if (MyLightManager::GetInstance()->GetLightCount() == 0) {
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "No lights in the scene. Add some lights above!");
                }
            }
            
        } else {
            ImGui::Text("Lighting System: Not Initialized");
            ImGui::Text("The lighting system failed to initialize properly.");
        }
        
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
    this->globalConstantData.cameraPosition = this->activeCamera->transform->position;

    //* Update Lighting System
    if (MyLightManager::GetInstance()) {
        // Animate the moving point light (second light, index 1)
        static float lightTime = 0.0f;
        lightTime += this->deltaTime;

        if (MyLightManager::GetInstance()->GetLightCount() > 1) {
            auto movingPointLight = std::dynamic_pointer_cast<MyPointLight>(MyLightManager::GetInstance()->GetLight(1));
            if (movingPointLight) {
                // More dramatic circular motion around the center, varying height
                float radius = 6.0f; // Increased radius
                movingPointLight->transform->position.x = cos(lightTime * 0.8f) * radius; // Slower but more visible
                movingPointLight->transform->position.z = sin(lightTime * 0.8f) * radius;
                movingPointLight->transform->position.y = 3.0f + sin(lightTime * 1.5f) * 2.0f; // Higher and more dramatic
                
                // Also animate the color for more visual feedback
                float colorPhase = sin(lightTime * 2.0f) * 0.3f + 0.7f; // Pulsating between 0.4 and 1.0
                movingPointLight->SetColor(MyVector3(0.3f * colorPhase, 0.8f * colorPhase, 1.0f * colorPhase));
            }
        }

        // Animate the spot light rotation (if it exists - should be index 3)
        if (MyLightManager::GetInstance()->GetLightCount() > 3) {
            auto spotLight = std::dynamic_pointer_cast<MySpotLight>(MyLightManager::GetInstance()->GetLight(3));
            if (spotLight) {
                // More dramatic rotation and also move the position
                spotLight->transform->rotation.y = sin(lightTime * 0.7f) * 90.0f; // Wider swing
                spotLight->transform->rotation.x = -45.0f + sin(lightTime * 0.5f) * 20.0f; // Vertical swing too
                
                // Move the spot light position slightly
                spotLight->transform->position.x = 4.0f + cos(lightTime * 0.6f) * 1.5f;
                spotLight->transform->position.z = 3.0f + sin(lightTime * 0.6f) * 1.5f;
            }
        }

        // Animate directional light (index 0) rotation for dramatic effect
        if (MyLightManager::GetInstance()->GetLightCount() > 0) {
            auto dirLight = std::dynamic_pointer_cast<MyDirectionalLight>(MyLightManager::GetInstance()->GetLight(0));
            if (dirLight) {
                // Slow rotation like the sun moving across the sky
                dirLight->transform->rotation.y = 45.0f + sin(lightTime * 0.3f) * 30.0f;
                dirLight->transform->rotation.x = -30.0f + cos(lightTime * 0.2f) * 15.0f;
            }
        }

        // Update lighting data for GPU
        MyLightManager::GetInstance()->SetNeedsUpdate(true);
        MyLightManager::GetInstance()->UpdateLightingData();
        
        // Update the GPU constant buffer every frame for animations
        MyLightManager::GetInstance()->UpdateLightingConstantBuffer();
    }
}

void MyAppWindow::UpdateConstantBuffer() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Updating constant buffer..." << std::endl;
    this->globalConstantBuffer->Update(MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext(), &this->globalConstantData);
    
    // Set constant buffer for standard shaders
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->globalConstantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->hullShader, this->globalConstantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->domainShader, this->globalConstantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->globalConstantBuffer);
    
    // ALSO set constant buffer for lighting shaders (they need transform matrices too!)
    if (this->lightingVertexShader && this->lightingPixelShader) {
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->lightingVertexShader, this->globalConstantBuffer);
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(this->lightingPixelShader, this->globalConstantBuffer);
    }
}

void MyAppWindow::UpdateShaders() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Updating shaders..." << std::endl;

    if (useLightingShaders && lightingVertexShader && lightingPixelShader) {
        // Use lighting shaders
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(this->lightingVertexShader);
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(this->lightingPixelShader);

        // Update lighting constant buffer
        if (MyLightManager::GetInstance()) {
            auto deviceContext = MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext();
            auto lightingBuffer = MyLightManager::GetInstance()->GetLightingConstantBuffer();
            if (lightingBuffer) {
                // Set lighting constant buffer to slot 1 (register(b1))
                deviceContext->SetConstantBuffer(this->lightingVertexShader, lightingBuffer, 1);
                deviceContext->SetConstantBuffer(this->lightingPixelShader, lightingBuffer, 1);
            }
        }
    }
    else {
        // Use standard shaders
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);
    }

    // Set primitive topology based on tessellation setting
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetPrimitiveTopology(useTessellation);

    // Set tessellation shaders based on mode and toggle
    if (useTessellation) {
        if (useLightingShaders) {
            // Use lighting tessellation shaders (pass-through)
            MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetHullShader(this->lightingHullShader);
            MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetDomainShader(this->lightingDomainShader);
        } else {
            // Use standard tessellation shaders
            MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetHullShader(this->hullShader);
            MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetDomainShader(this->domainShader);
        }
    } else {
        // Disable tessellation completely
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetHullShader(nullptr);
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetDomainShader(nullptr);
    }
}

void MyAppWindow::DrawLoop() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Drawing meshes..." << std::endl;
    
    // Use lighting shaders if enabled, otherwise use standard shaders
    MyVertexShaderPtr vertexShaderToUse = this->useLightingShaders ? this->lightingVertexShader : this->vertexShader;
    MyPixelShaderPtr pixelShaderToUse = this->useLightingShaders ? this->lightingPixelShader : this->pixelShader;
    
    for (MyMeshPtr mesh : this->meshes) {
        mesh->Draw(vertexShaderToUse, this->hullShader, this->domainShader, pixelShaderToUse,
            this->activeCamera->transform->worldMatrix, this->activeCamera->projectionMatrix, this->globalConstantData.time);
        
        // If using lighting shaders, set the lighting constant buffer after each mesh draw
        // (since mesh->Draw() sets its own constant buffer which might override our lighting buffer)
        if (this->useLightingShaders && MyLightManager::GetInstance()) {
            auto deviceContext = MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext();
            auto lightingBuffer = MyLightManager::GetInstance()->GetLightingConstantBuffer();
            if (lightingBuffer) {
                // Re-set lighting constant buffer to slot 1 (register(b1))
                deviceContext->SetConstantBuffer(this->lightingVertexShader, lightingBuffer, 1);
                deviceContext->SetConstantBuffer(this->lightingPixelShader, lightingBuffer, 1);
            }
        }
    }
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyAppWindow::OnCreate() {
    PERFORMANCE_TIMER("WINDOW", "MyAppWindow::OnCreate");
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnCreate called" << std::endl;
    LOG_INFO("WINDOW", "MyAppWindow::OnCreate - Initializing window");

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
    LOG_INFO("WINDOW", "Creating swap chain");
    swapChain = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateSwapChain(this->windowHandle, this->width, this->height);

    LOG_INFO("WINDOW", "Initializing shaders");
    this->InitializeShaders();

    LOG_INFO("WINDOW", "Initializing lighting shaders");
    this->InitializeLightingShaders();

    LOG_INFO("WINDOW", "Initializing constant data");
    this->InitializeConstantData();

    LOG_INFO("WINDOW", "Initializing lighting system");
    this->InitializeLightingSystem();

    LOG_INFO("WINDOW", "Running debug launch function");
    this->DebugLaunchFunction();

    LOG_INFO("WINDOW", "MyAppWindow::OnCreate completed successfully");
}

void MyAppWindow::OnUpdate() {
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: MyAppWindow::OnUpdate called" << std::endl;

    // Early exit if window is marked for closing to avoid updating systems unnecessarily
    if (this->shouldCloseWindow) {
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: Window marked for closing, skipping frame updates" << std::endl;
        // Still send the close message at the end
        ::SendMessage(this->windowHandle, WM_CLOSE, 0, 0);
        return;
    }

    MyWindow::OnUpdate();
    MyInputSystem::GetInstance()->Update();
    this->UpdateObjects();

    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, MyVector4(0.3f, 0.3f, 0.3f, 1.0f));
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetViewPortSize(this->width, this->height);


    this->UpdateConstantBuffer();
    this->UpdateShaders();
    // Set texture for the current pixel shader (lighting or standard)
    if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Setting texture: " << this->sampleTexture << std::endl;
    MyPixelShaderPtr currentPixelShader = this->useLightingShaders ? this->lightingPixelShader : this->pixelShader;
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetTexture(currentPixelShader, this->sampleTexture);

    // Set sampler state for pixel shader
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetSamplerState();

    this->DrawLoop();

    this->ImGuiUpdate();
    if (this->swapChain) {
        if (LOG_INFO_WINDOW_UPDATE) std::cout << "[INFO]: Presenting swap chain" << std::endl;
        this->swapChain->Present(true);
    }

    this->UpdateDeltaTime();

    // Check if window should be closed at the end of the frame
    if (this->shouldCloseWindow) {
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: Closing window at end of frame" << std::endl;
        ::SendMessage(this->windowHandle, WM_CLOSE, 0, 0);
    }
}

void MyAppWindow::OnDestroy() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO]: MyAppWindow::OnDestroy called" << std::endl;

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Removing MyAppWindow as input listener" << std::endl;
    MyInputSystem::GetInstance()->RemoveListener(this);

    // Clean up lighting system
    MyLightManager::Release();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    MyWindow::OnDestroy();

    // Clean up rendering resources
    this->vertexBuffer = nullptr;
    this->indexBuffer = nullptr;
    this->globalConstantBuffer = nullptr;
    this->hullShader = nullptr;
    this->domainShader = nullptr;
    this->vertexShader = nullptr;
    this->pixelShader = nullptr;
    this->lightingVertexShader = nullptr;
    this->lightingPixelShader = nullptr;
    this->lightingHullShader = nullptr;
    this->lightingDomainShader = nullptr;
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
    case VK_ESCAPE:
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: ESC pressed, requesting window close at end of frame" << std::endl;
        // Request window close at the end of the frame instead of immediately
        this->RequestWindowClose();
        break;
    case '1':
        this->useLightingShaders = !this->useLightingShaders;
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: 1 pressed, toggling shaders. Now using: " 
                                      << (this->useLightingShaders ? "Lighting Shaders" : "Standard Shaders") << std::endl;
        break;
    case '2':
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: 2 pressed, debugging normals (check console for instructions)" << std::endl;
        std::cout << "\n=== LIGHTING DEBUG INFO ===" << std::endl;
        std::cout << "Press '1' to toggle between standard and lighting shaders" << std::endl;
        std::cout << "Current mode: " << (this->useLightingShaders ? "Lighting Shaders" : "Standard Shaders") << std::endl;
        std::cout << "You should see:" << std::endl;
        std::cout << "- Standard mode: Just textured cubes" << std::endl;
        std::cout << "- Lighting mode: Static light from right side, left sides should be BLACK" << std::endl;
        std::cout << "If lighting mode looks the same as standard, normals might not be working!" << std::endl;
        std::cout << "=========================\n" << std::endl;
        break;
    case '3':
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: 3 pressed, switching to debug normals shader temporarily" << std::endl;
        // Temporarily use debug normals - we'll implement this if needed
        std::cout << "Debug normals: Each face should show different colors (Red=+X, Green=+Y, Blue=+Z)" << std::endl;
        break;
    case 'M':
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: M pressed, wireframe mode enabled" << std::endl;
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->ToggleWireframeMode(true);
        break;
    case 'N':
        if (LOG_INFO_WINDOW) std::cout << "[INFO]: N pressed, wireframe mode disabled" << std::endl;
        MyGraphicsEngine::GetInstance()->GetRenderSystem()->ToggleWireframeMode(false);
        break;
    case 'L':
        this->freeMouse = !this->freeMouse;
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

void MyAppWindow::InitializeLightingSystem() {
    PERFORMANCE_TIMER("WINDOW", "InitializeLightingSystem");
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Initializing lighting system" << std::endl;

    // Create lighting manager
    MyLightManager::Create();
    if (!MyLightManager::GetInstance()) {
        if (LOG_INFO_LIGHTING) std::cout << "[ERROR]: Failed to create MyLightManager" << std::endl;
        throw std::exception("Failed to create MyLightManager");
        return;
    }

    // Create lighting constant buffer (lights will be added in DebugLaunchFunction)
    MyLightManager::GetInstance()->CreateLightingConstantBuffer();

    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Lighting system core initialized" << std::endl;
}