#pragma once
#include "Game/Lighting/MyLight.hpp"

namespace DX3D {
    class MyDirectionalLight : public MyLight {
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyDirectionalLight(const MyVector3& color = MyVector3(1.0f, 1.0f, 1.0f), 
                          float intensity = 1.0f, 
                          float range = 1000.0f);
        virtual ~MyDirectionalLight() = default;

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Override to provide directional light specific data
        MyLightData GetLightData() const override;
        
        // Set the direction directly (alternative to using transform rotation)
        void SetDirection(const MyVector3& direction);
        MyVector3 GetDirection() const;

    private:
        MyVector3 explicitDirection;
        bool useExplicitDirection;
    };

} // namespace DX3D
