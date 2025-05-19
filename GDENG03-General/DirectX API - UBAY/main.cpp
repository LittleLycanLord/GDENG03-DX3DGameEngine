#include "Window/MyAppWindow.hpp"

int main() {
    DX3D::MyAppWindow appWindow;
    if (!appWindow.Init()) {
        return -1;
    }
    while (appWindow.IsRunning()) {
        appWindow.Broadcast();
    }
    return 0;
}