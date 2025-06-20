#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"
#include <string>
#include <iostream>

int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 768;
float WINDOW_WIDTH_LIMITS = 1024.0f * 0.0012f;
float WINDOW_HEIGHT_LIMITS = 768.0f * 0.0012f;
int WINDOW_REFRESH_RATE = 60;

// Logging toggles
bool LOG_INFO_WINDOW = false;
bool LOG_INFO_GRAPHICS_ENGINE = false;
bool LOG_INFO_SWAPCHAIN = false;
bool LOG_INFO_DEVICECONTEXT = false;
bool LOG_INFO_VERTEXBUFFER = false;
bool LOG_INFO_CONSTANTBUFFER = false;
bool LOG_INFO_INDEXBUFFER = false;
bool LOG_INFO_VERTEXSHADER = false;
bool LOG_INFO_PIXELSHADER = false;
bool LOG_INFO_INPUTSYSTEM = false;

bool LOG_BALL_BOUNCES = false;
bool LOG_BALL_CONTROLS = true;
float MAXIMUM_BALL_SPEED = 3.0f;
float MINIMUM_BALL_SPEED = 0.1f;

// Directory for shader files
extern const std::wstring VERTEX_SHADER_DIRECTORY = L"Shaders/Vertex/BouncingCirclesVertexShader.hlsl";
extern const std::wstring PIXEL_SHADER_DIRECTORY = L"Shaders/Pixel/BouncingCirclesPixelShader.hlsl";

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

