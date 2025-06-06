#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"

namespace DX3D {
    class MyGraphicsEngine {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyGraphicsEngine* instance;
        
        MyRenderSystem* renderSystem{ nullptr };

        //* ╔════════════════════════════╗
        //* ║ Singleton Instance Accessor ║
        //* ╚════════════════════════════╝
    public:
        static MyGraphicsEngine* GetInstance() {
            static MyGraphicsEngine graphicsEngine;
            return &graphicsEngine;
        }

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    private:
        MyGraphicsEngine();
        ~MyGraphicsEngine();
    public:

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        static void Create();
        static void Release();
        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyRenderSystem* GetRenderSystem() const { return this->renderSystem; }
    };
} // namespace DX3D

