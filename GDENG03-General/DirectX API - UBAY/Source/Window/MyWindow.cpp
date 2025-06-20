#include "Window/MyWindow.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyWindow::MyWindow() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow constructed" << std::endl;
}
MyWindow::~MyWindow() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow destructed" << std::endl;
}

//* ╔═════════════════════════════════╗
//* ║ Magical Shit I Don't Understand ║
//* ╚═════════════════════════════════╝

LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParameters, LPARAM lParameters) {
    switch (message) {
    case WM_CREATE: {
            MyWindow* windowInstance = (MyWindow*)((LPCREATESTRUCT)lParameters)->lpCreateParams;
            SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)windowInstance);
            windowInstance->SetWindowHandle(windowHandle);
            windowInstance->OnCreate();
            break;
        }
    case WM_DESTROY: {
            MyWindow* windowInstance = (MyWindow*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
            windowInstance->OnDestroy();
            ::PostQuitMessage(0);
            break;
        }
    default:
        return DefWindowProc(windowHandle, message, wParameters, lParameters);
    }
    return NULL;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyWindow::Initialize() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::Initialize called" << std::endl;
    WNDCLASSEX windowClass;
    windowClass.cbClsExtra = NULL;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.cbWndExtra = NULL;
    windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hInstance = (NULL);
    windowClass.lpszClassName = L"MyWindowClass";
    windowClass.lpszMenuName = L"";
    windowClass.style = NULL;
    windowClass.lpfnWndProc = WindowProcedure;

    if (!::RegisterClassEx(&windowClass)) {
        if (LOG_INFO_WINDOW) std::cout << "[ERROR] : RegisterClassEx failed" << std::endl;
        return false;
    }

    windowHandle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Conrad Ubay | DirectX 3D Engine Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL,
        NULL, this);

    if (!windowHandle) {
        if (LOG_INFO_WINDOW) std::cout << "[ERROR] : CreateWindowEx failed" << std::endl;
        return false;
    }

    ::ShowWindow(windowHandle, SW_SHOW);
    ::UpdateWindow(windowHandle);

    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Window created and shown" << std::endl;
    this->running = true;
    return true;
}
bool MyWindow::Broadcast() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::Broadcast called" << std::endl;

    this->OnUpdate();

    MSG message;
    while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0) {
        ::TranslateMessage(&message);
        ::DispatchMessage(&message);
    }
    Sleep(0);
    return true;
}

bool MyWindow::Release() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::Release called" << std::endl;
    if (!::DestroyWindow(windowHandle)) {
        if (LOG_INFO_WINDOW) std::cout << "[ERROR] : DestroyWindow failed" << std::endl;
        return false;
    }
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Window destroyed" << std::endl;
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyWindow::OnCreate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::OnCreate called" << std::endl;
}

void MyWindow::OnUpdate() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::OnUpdate called" << std::endl;
}

void MyWindow::OnDestroy() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::OnDestroy called" << std::endl;
    this->running = false;
}
