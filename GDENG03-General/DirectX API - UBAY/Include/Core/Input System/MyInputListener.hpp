#pragma once
#include "Math/MyScreenPoint.hpp"

namespace DX3D {
    class MyInputListener {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyInputListener();
        ~MyInputListener();

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
        //* Keyboard Input Events
        virtual void OnKeyDown(int keyCode) = 0;
        virtual void OnKeyHold(int keyCode) = 0;
        virtual void OnKeyUp(int keyCode) = 0;

        //* Mouse Input Events
        virtual void OnMouseMove(const MyScreenPoint& deltaMousePosition) = 0;
        virtual void OnLMBDown(const MyScreenPoint& mousePosition) = 0;
        virtual void OnLMBHold(const MyScreenPoint& deltaMousePosition) = 0;
        virtual void OnLMBUp(const MyScreenPoint& mousePosition) = 0;
        virtual void OnRMBDown(const MyScreenPoint& mousePosition) = 0;
        virtual void OnRMBHold(const MyScreenPoint& deltaMousePosition) = 0;
        virtual void OnRMBUp(const MyScreenPoint& mousePosition) = 0;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

