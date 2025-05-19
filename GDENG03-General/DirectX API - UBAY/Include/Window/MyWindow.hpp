#pragma once
#include <Windows.h>

namespace DX3D {
    class MyWindow {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        bool running{false};
    protected:
        HWND windowHandle{NULL};
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
        bool Init();
        bool Broadcast();
        bool Release();

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        virtual void OnCreate() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDestroy();

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        bool IsRunning() const { return running; }
    };
} // namespace DX3D

