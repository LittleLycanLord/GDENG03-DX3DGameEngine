#include "Core/Input System/MyInputSystem.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"
#include <string>
#include <iostream>

bool LOG_WARNING_GENERAL = true;
bool LOG_ERROR_GENERAL = true;

// Logging toggles
bool LOG_INFO_WINDOW = false;
bool LOG_INFO_WINDOW_UPDATE = false;
bool LOG_INFO_CAMERA = false;
bool LOG_INFO_GRAPHICS_ENGINE = false;
bool LOG_INFO_RENDER_SYSTEM = false;
bool LOG_INFO_SWAP_CHAIN = false;
bool LOG_INFO_DEVICE_CONTEXT = false;
bool LOG_INFO_VERTEX_BUFFER = false;
bool LOG_INFO_CONSTANT_BUFFER = false;
bool LOG_INFO_INDEX_BUFFER = false;

bool LOG_INFO_HULL_SHADER = false;
bool LOG_INFO_DOMAIN_SHADER = false;
bool LOG_INFO_VERTEX_SHADER = false;
bool LOG_INFO_PIXEL_SHADER = false;

bool LOG_INFO_INPUT_SYSTEM_KEYBOARD = false;
bool LOG_INFO_INPUT_SYSTEM_MOUSE = false;

bool LOG_INFO_RESOURCE_SYSTEM = false;
bool LOG_INFO_RESOURCE = false;
bool LOG_INFO_TEXTURE_MANAGER = false;
bool LOG_INFO_TEXTURE = false;
bool LOG_INFO_MESH_MANAGER = false;
bool LOG_INFO_MESH = false;

extern const std::wstring LAYOUT_SHADER_DIRECTORY = L"Shaders/Layout/MeshVertexLayoutShader.hlsl";
extern const std::wstring HULL_SHADER_DIRECTORY = L"Shaders/Hull/TexturedTeapotHullShader.hlsl";
extern const std::wstring DOMAIN_SHADER_DIRECTORY = L"Shaders/Domain/TexturedTeapotDomainShader.hlsl";
extern const std::wstring VERTEX_SHADER_DIRECTORY = L"Shaders/Vertex/TexturedTeapotVertexShader.hlsl";
extern const std::wstring PIXEL_SHADER_DIRECTORY = L"Shaders/Pixel/TexturedTeapotPixelShader.hlsl";
extern const std::wstring SAMPLE_TEXTURE_DIRECTORY = L"Assets/Textures/CheckerBoard.jpg";
extern const std::wstring SAMPLE_MESH_DIRECTORY = L"Assets/Meshes/Cube.obj";
extern const std::wstring IMGUI_LOGO_DIRECTORY = L"Assets/Textures/dlsu_logo.png";
using namespace DX3D;

int main() {
    std::cout << "[INFO]: Application started" << std::endl;

    try {
        MyGraphicsEngine::Create();
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Failed to create MyGraphicsEngine: " << ex.what() << std::endl;
        return -1;
    }
    try {
        MyInputSystem::Create();
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Failed to create MyInputSystem: " << ex.what() << std::endl;
        return -2;
    }

    try {
        MyAppWindow appWindow;
        MyInputSystem::GetInstance()->windowHandle = appWindow.windowHandle;
        while (appWindow.IsRunning());
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception: " << ex.what() << std::endl;
        MyGraphicsEngine::Release();
        MyInputSystem::Release();
        return -1;
    }
    std::cout << "[INFO]: Application exiting" << std::endl;

    MyGraphicsEngine::Release();
    MyInputSystem::Release();
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] MyGraphicsEngine released" << std::endl;

    return 0;
}

