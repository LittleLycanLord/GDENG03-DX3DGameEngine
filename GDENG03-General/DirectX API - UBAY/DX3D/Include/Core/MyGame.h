#pragma once
#include "Core/MyBase.h"
#include "Core/DX3DCore.h"

namespace DX3D {
    class MyGame : public MyBase {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyWindow* windowDisplay{};
        bool running = true;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyGame();
        virtual ~MyGame() override;

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        virtual void Run() final;

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        bool IsRunning();
    };
} // namespace DX3D

