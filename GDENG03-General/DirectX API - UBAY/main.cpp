#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"
#include <string>
#include <iostream>

// Logging toggles
bool LOG_INFO_WINDOW = false;
bool LOG_INFO_GRAPHICS_ENGINE = false;
bool LOG_INFO_SWAPCHAIN = false;
bool LOG_INFO_DEVICECONTEXT = false;
bool LOG_INFO_VERTEXBUFFER = false;
bool LOG_INFO_CONSTANTBUFFER = false;
bool LOG_INFO_INDEXBUFFER = true;
bool LOG_INFO_VERTEXSHADER = false;
bool LOG_INFO_PIXELSHADER = false;
bool LOG_INFO_INPUTSYSTEM = false;


// Directory for shader files
extern const std::wstring VERTEX_SHADER_DIRECTORY = L"Shaders/Vertex/RainbowCubeVertexShader.hlsl";
extern const std::wstring PIXEL_SHADER_DIRECTORY = L"Shaders/Pixel/RainbowCubePixelShader.hlsl";

using namespace DX3D;

int main() {
    std::cout << "[INFO] : Application started" << std::endl;
    MyAppWindow appWindow;
    if (!appWindow.Initialize()) {
        std::cout << "[ERROR] : Failed to initialize application window" << std::endl;
        return -1;
    }
    while (appWindow.IsRunning()) {
        appWindow.Broadcast();
    }
    std::cout << "[INFO] : Application exiting" << std::endl;
    return 0;
}

