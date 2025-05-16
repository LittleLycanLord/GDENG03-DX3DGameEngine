#pragma once
#include "Graphics/MyGraphicsEngine.h"
#include <d3d11.h>

namespace DX3D {
    class MyVertexBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        UINT size_vertex{ 0 };
        UINT size_list{ 0 };
        ID3D11Buffer* buffer{ nullptr };
        ID3D11InputLayout* layout{ nullptr };
        friend class MyDeviceContext;

    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVertexBuffer();
        ~MyVertexBuffer();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
        bool release();

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


