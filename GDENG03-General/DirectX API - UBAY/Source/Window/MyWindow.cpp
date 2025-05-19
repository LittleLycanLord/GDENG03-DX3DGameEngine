#include "Window/MyWindow.hpp"
//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyWindow::MyWindow() {}
DX3D::MyWindow::~MyWindow() {}

//* ╔═════════════════════════════════╗
//* ║ Magical Shit I Don't Understand ║
//* ╚═════════════════════════════════╝

DX3D::MyWindow* windowProcedurePointer = nullptr;
LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParameters, LPARAM lParameters) {
    switch (message) {
    case WM_CREATE:
        windowProcedurePointer->OnCreate();
        break;
    case WM_DESTROY:
        windowProcedurePointer->OnDestroy();
        ::PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(windowHandle, message, wParameters, lParameters);
    }
    return NULL;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool DX3D::MyWindow::Init() {
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

    if (!::RegisterClassEx(&windowClass))
        return false;

    if (!windowProcedurePointer)
        windowProcedurePointer = this;

    windowHandle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Conrad Ubay | DirectX 3D Engine Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        1280, 720, NULL, NULL,
        NULL, NULL);

    if (!windowHandle)
        return false;

    ::ShowWindow(windowHandle, SW_SHOW);
    ::UpdateWindow(windowHandle);

    this->running = true;
    return true;
}
bool DX3D::MyWindow::Broadcast() {
    MSG message;
    while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0) {
        ::TranslateMessage(&message);
        ::DispatchMessage(&message);
    }
    OnUpdate();
    Sleep(0);
    return true;
}

bool DX3D::MyWindow::Release() {
    if (!::DestroyWindow(windowHandle))
        return false;
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void DX3D::MyWindow::OnDestroy() {
    this->running = false;
}
