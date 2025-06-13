#pragma once
#include <Windows.h>
#include <WinUser.h>
#include <exception>

namespace DX3D {
    class MyWindow {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        bool running{ false };
        bool initialized{ false };
    protected:
    public:
        HWND windowHandle{ nullptr };

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
        bool Broadcast();
    public:

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        virtual void OnCreate();
        virtual void OnUpdate();
        virtual void OnDestroy();

        virtual void OnSetFocus();
        virtual void OnKillFocus();

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        bool IsRunning() {
            if (this->running)
                this->Broadcast();
            return this->running;
        }
        RECT GetWindowRect() const {
            RECT rect;
            GetClientRect(windowHandle, &rect);
            return rect;
        }
    };
} // namespace DX3D

