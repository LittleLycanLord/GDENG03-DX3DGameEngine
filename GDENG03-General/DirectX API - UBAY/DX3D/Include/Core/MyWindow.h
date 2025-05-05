#pragma once
#include "Core/MyBase.h"
#include <Windows.h>

namespace DX3D {
    class MyWindow : public MyBase {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        void* windowHandle{};
    public:
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyWindow();
        virtual ~MyWindow() override;

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:

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

