#pragma once
#include <map>
#include <iostream>
#include <Windows.h>
#include <exception>
#include "Core/Input System/MyInputListener.hpp"
#include "Math/MyScreenPoint.hpp"

namespace DX3D {
    class MyInputSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyInputSystem* instance;

        std::map<MyInputListener*, MyInputListener*> inputListeners;
        unsigned char newKeyStates[256] = { 0 };
        unsigned char oldKeyStates[256] = { 0 };

        bool lockMouse = true;
        bool firstFrame = true;
        float rawMouseDeltaX = 0.0f;
        float rawMouseDeltaY = 0.0f;
        MyScreenPoint newMousePosition = { 0, 0 };
        MyScreenPoint oldMousePosition = { 0, 0 };
        MyScreenPoint deltaMousePosition = { 0, 0 };
    public:
        bool ignoreNextMouseDelta = false;
        float windowWidth;
        float windowHeight;

        //* ╔═════════════════════════════╗
        //* ║ Singleton Instance Accessor ║
        //* ╚═════════════════════════════╝
    public:
        HWND windowHandle;
        static MyInputSystem* GetInstance() {
            static MyInputSystem instance;
            return &instance;
        }

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    private:
        MyInputSystem();
        ~MyInputSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        static void Create();
        static void Release();
        void Update();
        void AddListener(MyInputListener* inputListener);
        void RemoveListener(MyInputListener* inputListener);

        void AddRawMouseDelta(float deltaX, float deltaY);
        void SetCursorPosition(const MyScreenPoint& position);
        void SetCursorVisibility(bool showCursor);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:

    };
} // namespace DX3D

