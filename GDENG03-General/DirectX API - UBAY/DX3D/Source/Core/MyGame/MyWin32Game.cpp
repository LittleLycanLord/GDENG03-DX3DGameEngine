#include "Core/MyGame.h"
#include "Windows.h"

void DX3D::MyGame::Run() {
    MSG message{};
    while (running) {
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message); // Translate the message
            DispatchMessage(&message); // Dispatch the message to the window procedure
        } // Process messages in the message queue
        Sleep(1);
    }
}