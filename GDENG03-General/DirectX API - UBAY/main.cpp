#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"

int main() {
    DX3D::MyAppWindow appWindow;
    if (!appWindow.Initialize()) {
        return -1;
    }
    while (appWindow.IsRunning()) {
        appWindow.Broadcast();
    }
    return 0;
}

    