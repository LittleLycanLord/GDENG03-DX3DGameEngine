#pragma once
#include "Core/Input System/MyInputListener.hpp"
#include "Math/MyScreenPoint.hpp"
#include <map>
#include <iostream>
#include <Windows.h>

namespace DX3D {
    class MyInputSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        std::map<MyInputListener*, MyInputListener*> inputListeners;
        unsigned char newKeyStates[256] = { 0 };
        unsigned char oldKeyStates[256] = { 0 };

        bool firstFrame = true;
        MyScreenPoint newMousePosition = { 0, 0 };
        MyScreenPoint oldMousePosition = { 0, 0 };
        MyScreenPoint deltaMousePosition = { 0, 0 };

    public:
        static MyInputSystem* GetInstance() {
            static MyInputSystem instance;
            return &instance;
        }
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyInputSystem();
        ~MyInputSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Update();
        void AddListener(MyInputListener* inputListener);
        void RemoveListener(MyInputListener* inputListener);

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

