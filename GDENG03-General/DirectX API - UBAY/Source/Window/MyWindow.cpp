#include "Window/MyWindow.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include <iostream>

using namespace DX3D;

extern bool LOG_INFO_WINDOW;

//* ╔═════════════════════════════════╗
//* ║ Magical Shit I Don't Understand ║
//* ╚═════════════════════════════════╝

LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParameters, LPARAM lParameters) {
    switch (message) {
    case WM_CREATE: {

            break;
        }
    case WM_SETFOCUS: {
            MyWindow* windowInstance = (MyWindow*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
            if (windowInstance) windowInstance->OnSetFocus();
            break;
        }
    case WM_KILLFOCUS: {
            MyWindow* windowInstance = (MyWindow*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
            if (windowInstance) windowInstance->OnKillFocus();
            break;
        }
    case WM_DESTROY: {
            MyWindow* windowInstance = (MyWindow*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
            if (windowInstance) windowInstance->OnDestroy();
            PostQuitMessage(0);
            break;
        }
    default:
        return DefWindowProc(windowHandle, message, wParameters, lParameters);
    }
    return NULL;
}

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyWindow::MyWindow() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow constructed" << std::endl;

    WNDCLASSEX windowClass = {};
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
        if (LOG_INFO_WINDOW) throw std::exception("RegisterClassEx failed");
    }

    windowHandle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Conrad Ubay | DirectX 3D Engine Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        1280, 720, NULL, NULL,
        NULL, NULL);

    if (!windowHandle) {
        if (LOG_INFO_WINDOW) throw std::exception("CreateWindowEx failed");
    } else {
        ShowWindow(windowHandle, SW_SHOW);
        UpdateWindow(windowHandle);
    }

    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Window created and shown" << std::endl;
    this->running = true;
}
MyWindow::~MyWindow() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow destructed" << std::endl;

    DestroyWindow(windowHandle);
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : Window destroyed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyWindow::Broadcast() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::Broadcast called" << std::endl;

    MSG message;

    if (!this->initialized) {
        // MyWindow* windowInstance = (MyWindow*)((LPCREATESTRUCT)lParameters)->lpCreateParams;
        SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)this);
        this->OnCreate();
        this->initialized = true;
    }

    this->OnUpdate();

    while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0) {
        ::TranslateMessage(&message);
        ::DispatchMessage(&message);
    }
    Sleep(0);
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
void MyWindow::OnSetFocus() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::OnSetFocus called" << std::endl;
}
void MyWindow::OnKillFocus() {
    if (LOG_INFO_WINDOW) std::cout << "[INFO] : MyWindow::OnUnfocus called" << std::endl;
}
