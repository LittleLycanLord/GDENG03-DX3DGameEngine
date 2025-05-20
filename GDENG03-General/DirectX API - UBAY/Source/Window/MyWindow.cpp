#include "Window/MyWindow.hpp"
#include "Graphics/MyGraphicsEngine.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyWindow::MyWindow() {}
MyWindow::~MyWindow() {}

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

    windowHandle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Conrad Ubay | DirectX 3D Engine Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        1280, 720, NULL, NULL,
        NULL, this);

    if (!windowHandle)
        return false;

    ::ShowWindow(windowHandle, SW_SHOW);
    ::UpdateWindow(windowHandle);

    this->running = true;
    return true;
}
bool MyWindow::Broadcast() {
    MSG message;
    
    this->OnUpdate();

    while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0) {
        ::TranslateMessage(&message);
        ::DispatchMessage(&message);
    }
    Sleep(0);
    return true;
}

bool MyWindow::Release() {
    if (!::DestroyWindow(windowHandle))
        return false;
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyWindow::OnCreate() {

}

void MyWindow::OnUpdate() {

}

void MyWindow::OnDestroy() {
    this->running = false;
}
