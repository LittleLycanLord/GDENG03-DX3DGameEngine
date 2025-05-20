#pragma once
#include <Windows.h>
#include <WinUser.h>

namespace DX3D {
    class MyWindow {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        bool running{ false };
    protected:
        HWND windowHandle{ nullptr };
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyWindow();
        ~MyWindow();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Initialize();
        bool Broadcast();
        bool Release();

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        virtual void OnCreate();
        virtual void OnUpdate();
        virtual void OnDestroy();

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        bool IsRunning() const { return running; }
        RECT GetWindowRect() const {
            RECT rect;
            GetClientRect(windowHandle, &rect);
            return rect;
        }
        void SetWindowHandle(HWND windowHandle) { this->windowHandle = windowHandle; }
    };
} // namespace DX3D

