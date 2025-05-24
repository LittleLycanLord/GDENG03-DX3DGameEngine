#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"
#include <string>

// Logging toggles
bool LOG_INFO_WINDOW = false;
bool LOG_INFO_GRAPHICS_ENGINE = false;
bool LOG_INFO_SWAPCHAIN = false;
bool LOG_INFO_VERTEXBUFFER = false;
bool LOG_INFO_DEVICECONTEXT = false;
bool LOG_INFO_SHADER = true;

// Directory for shader files
extern const std::wstring VERTEX_SHADER_DIRECTORY = L"Shaders/Vertex/RainbowVertexShader.hlsl";
extern const std::wstring PIXEL_SHADER_DIRECTORY = L"Shaders/Pixel/RainbowPixelShader.hlsl";

using namespace DX3D;

int main() {
    MyAppWindow appWindow;
    if (!appWindow.Initialize()) {
        return -1;
    }
    while (appWindow.IsRunning()) {
        appWindow.Broadcast();
    }
    return 0;
}

