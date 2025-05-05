#include "Core/MyWindow.h"

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyWindow::MyWindow() {
    WNDCLASSEX windowClass = { };
    windowClass.cbSize = sizeof(WNDCLASSEX); // Size of the structure
    windowClass.lpszClassName = L"DX3DWindowClass"; // Window class name
    windowClass.lpfnWndProc = DefWindowProc; // Window procedure function 
    auto windowClassID = RegisterClassEx(&windowClass); // Register the window class

    if (!windowClassID) {
        // Handle error if window class registration fails
        MessageBox(NULL, L"Failed to register window class", L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    RECT windowRectangle = { 0, 0, 1280, 720 }; // Window rectangle dimensions
    AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU, FALSE); // Adjust the window rectangle

    windowHandle = CreateWindowEx(
        NULL, MAKEINTATOM(windowClassID), L"DX3D Window", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, NULL, NULL, NULL, NULL
    );

    if (!windowHandle) {
        // Handle error if window creation fails
        MessageBox(NULL, L"Failed to create window", L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    ShowWindow(static_cast<HWND>(windowHandle), SW_SHOW); // Show the window
    UpdateWindow(static_cast<HWND>(windowHandle)); // Update the window
}
DX3D::MyWindow::~MyWindow() {
    DestroyWindow(static_cast<HWND>(windowHandle)); // Destroy the window
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝