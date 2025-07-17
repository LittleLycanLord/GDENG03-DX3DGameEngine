#pragma once

// Standard includes
#include <vector>
#include <memory>
#include <iostream>
#include <string>

// TinyObjLoader
#include "tiny_obj_loader.h"

namespace DX3D {
    // Forward declarations to avoid circular dependencies
    class MyMeshVertex;
    class MyMatrix4x4;
    class MyVector2;
    class MyVector3;
    struct MyConstant;
    class MyVertexBuffer;
    class MyIndexBuffer;
    class MyConstantBuffer;
    class MyVertexShader;
    class MyHullShader;
    class MyDomainShader;
    class MyPixelShader;
    class MyLight;
    class MyTransform;

    // Smart pointer typedefs
    typedef std::shared_ptr<MyVertexBuffer> MyVertexBufferPtr;
    typedef std::shared_ptr<MyIndexBuffer> MyIndexBufferPtr;
    typedef std::shared_ptr<MyConstantBuffer> MyConstantBufferPtr;
    typedef std::shared_ptr<MyVertexShader> MyVertexShaderPtr;
    typedef std::shared_ptr<MyHullShader> MyHullShaderPtr;
    typedef std::shared_ptr<MyDomainShader> MyDomainShaderPtr;
    typedef std::shared_ptr<MyPixelShader> MyPixelShaderPtr;
    typedef std::shared_ptr<MyLight> MyLightPtr;

    class MyMesh {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        // TinyObjLoader data
        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warning, error;

        // Mesh data
        std::vector<MyMeshVertex> vertices;
        std::vector<unsigned int> indices;

        // DirectX resources
        MyVertexBufferPtr vertexBuffer;
        MyIndexBufferPtr indexBuffer;
        MyConstantBufferPtr constantBuffer;
        
        // Shader data
        void* layoutShaderByteCode{ nullptr };
        size_t layoutShaderSize{ 0 };

        // Constant buffer data
        MyConstant constantData;

        // Animation data
        float time{ 0.0f };

    public:
        std::shared_ptr<MyTransform> transform;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMesh(const wchar_t* resourcePath);
        ~MyMesh();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        void Update(float deltaTime);
        void Draw(MyVertexShaderPtr vertexShader, MyHullShaderPtr hullShader, 
                  MyDomainShaderPtr domainShader, MyPixelShaderPtr pixelShader,
                  const MyMatrix4x4& viewMatrix, const MyMatrix4x4& projectionMatrix, 
                  float currentTime, const std::vector<MyLightPtr>& sceneLights);

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyVertexBufferPtr GetVertexBuffer() const { return this->vertexBuffer; }
        MyIndexBufferPtr GetIndexBuffer() const { return this->indexBuffer; }
        MyConstantBufferPtr GetConstantBuffer() const { return this->constantBuffer; }
        size_t GetVertexCount() const { return this->vertices.size(); }
        size_t GetIndexCount() const { return this->indices.size(); }
    };
} // namespace DX3D
