#include "Core/Resource System/Managers/MyMesh.hpp"

using namespace DX3D;
extern bool LOG_INFO_MESH;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMesh::MyMesh(const wchar_t* resourcePath) : transform(std::make_shared<MyTransform>()), MyResource(resourcePath), attributes(),
shapes(),
materials(),
vertices(),
indices() {
    if (LOG_INFO_MESH) std::wcout << L"[INFO]: MyMesh constructed for " << resourcePath << std::endl;

    std::filesystem::path filePath = resourcePath;

    if (tinyobj::LoadObj(&this->attributes, &this->shapes, &this->materials, &this->warning, &this->error, filePath.string().c_str())) {
        {
            if (LOG_INFO_MESH) std::wcout << L"[INFO]: Loading MyMesh Vertices..." << std::endl;

            if (this->shapes.size() > 1) {
                std::cerr << "[ERROR]: Failed to load mesh from file" << std::endl;
                throw std::runtime_error("Failed to load mesh from file");
            }
            for (size_t shape = 0; shape < this->shapes.size(); shape++) {
                size_t indexOffset = 0;
                this->vertices.reserve(this->shapes[shape].mesh.indices.size());
                this->indices.reserve(this->shapes[shape].mesh.indices.size());

                for (size_t face = 0; face < this->shapes[shape].mesh.num_face_vertices.size(); face++) {
                    unsigned char vertexPerFace = this->shapes[shape].mesh.num_face_vertices[face];
                    for (unsigned char vertex = 0; vertex < vertexPerFace; vertex++) {
                        //* Vertex Reading
                        tinyobj::index_t index = (tinyobj::index_t)this->shapes[shape].mesh.indices[indexOffset + vertex];

                        //* POSITION
                        tinyobj::real_t x = (tinyobj::real_t)this->attributes.vertices[index.vertex_index * 3 + 0];
                        tinyobj::real_t y = (tinyobj::real_t)this->attributes.vertices[index.vertex_index * 3 + 1];
                        tinyobj::real_t z = (tinyobj::real_t)this->attributes.vertices[index.vertex_index * 3 + 2];

                        //* TEXCOORD
                        tinyobj::real_t u = (tinyobj::real_t)this->attributes.texcoords[index.texcoord_index * 2 + 0];
                        tinyobj::real_t v = (tinyobj::real_t)this->attributes.texcoords[index.texcoord_index * 2 + 1];

                        this->vertices.push_back(MyMeshVertex(MyVector3(x, y, z), MyVector2(u, v)));
                        this->indices.push_back((unsigned int)indexOffset + vertex);
                    }
                    indexOffset += vertexPerFace;
                }
            }
        }

        MyGraphicsEngine::GetInstance()->GetShaderByteCodeAndSize(&this->layoutShaderByteCode, &this->layoutShaderSize);
        this->vertexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexBuffer(&this->vertices[0], sizeof(MyMeshVertex), (UINT)this->vertices.size(), this->layoutShaderByteCode, this->layoutShaderSize);
        this->indexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateIndexBuffer(&this->indices[0], (UINT)this->indices.size());
    }
    else {
        if (!this->error.empty())
            std::cerr << "[ERROR]: Failed to load mesh from file: " << this->error << std::endl;
        else
            std::cerr << "[ERROR]: Failed to load mesh from file" << std::endl;

        throw std::runtime_error("Failed to load mesh from file");
    }
}
MyMesh::~MyMesh() {
    if (LOG_INFO_MESH) std::cout << "[INFO]: MyMesh destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyMesh::Update(float deltaTime) {
    this->transform->Update(deltaTime);
}
void MyMesh::Draw() {
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangles(this->indexBuffer->GetIndexCount(), 0, 0);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
