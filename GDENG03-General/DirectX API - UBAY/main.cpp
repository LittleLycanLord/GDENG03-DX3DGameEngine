#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"

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

    