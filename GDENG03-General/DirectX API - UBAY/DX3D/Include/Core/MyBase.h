#pragma once
#include <Core/DX3DCommon.h>

namespace DX3D {
    class MyBase {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    protected:
        MyLogger&logger;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        explicit MyBase(const BaseDescription& desc);
        virtual ~MyBase();

    protected:
        MyBase(const MyBase&) = delete;
        MyBase(MyBase&&) = delete;
        MyBase& operator = (const MyBase&) = delete;
        MyBase& operator=(MyBase&&) = delete;

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
        virtual MyLogger& getLogger() noexcept final;
    };


} // namespace DX3D

