#pragma once
#include "Game/Lighting/MyLight.hpp"
#include "Game/Lighting/MyDirectionalLight.hpp"
#include "Game/Lighting/MyPointLight.hpp"
#include "Game/Lighting/MySpotLight.hpp"
#include <vector>
#include <memory>

namespace DX3D {
    // Forward declarations
    class MyConstantBuffer;

    class MyLightManager {
        //* ╔═══════════════════════╗
        //* ║ Singleton Management  ║
        //* ╚═══════════════════════╝
    private:
        static MyLightManager* instance;
        MyLightManager();

    public:
        static void Create();
        static void Release();
        static MyLightManager* GetInstance();
        ~MyLightManager();

        //* ╔═══════════════════════╗
        //* ║ Constants & Types     ║
        //* ╚═══════════════════════╝
    public:
        static const int MAX_LIGHTS = 32;  // Maximum lights supported by shaders

        // GPU-compatible lighting data structure
        __declspec(align(16))
        struct LightingData {
            MyLightData lights[MAX_LIGHTS];  // Array of light data
            int numDirectionalLights;        // Count of directional lights
            int numPointLights;              // Count of point lights  
            int numSpotLights;               // Count of spot lights
            int totalActiveLights;           // Total number of active lights
            MyVector3 ambientLight;          // Global ambient lighting
            float ambientIntensity;          // Ambient light intensity
            float padding[8];                // Ensure 16-byte alignment
        };

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Light management
        void AddLight(std::shared_ptr<MyLight> light);
        void RemoveLight(std::shared_ptr<MyLight> light);
        void RemoveAllLights();
        
        // Convenience add functions
        std::shared_ptr<MyDirectionalLight> AddDirectionalLight(const MyVector3& color = MyVector3(1,1,1), float intensity = 1.0f);
        std::shared_ptr<MyPointLight> AddPointLight(const MyVector3& position, const MyVector3& color = MyVector3(1,1,1), float intensity = 1.0f, float range = 10.0f);
        std::shared_ptr<MySpotLight> AddSpotLight(const MyVector3& position, const MyVector3& direction, const MyVector3& color = MyVector3(1,1,1), float intensity = 1.0f, float range = 10.0f);
        
        // Light access
        const std::vector<std::shared_ptr<MyLight>>& GetLights() const { return lights; }
        std::shared_ptr<MyLight> GetLight(size_t index) const;
        size_t GetLightCount() const { return lights.size(); }
        
        // Light type counts
        int GetDirectionalLightCount() const;
        int GetPointLightCount() const;
        int GetSpotLightCount() const;
        
        // Ambient lighting
        void SetAmbientLight(const MyVector3& color, float intensity = 0.1f);
        MyVector3 GetAmbientLight() const { return ambientLight; }
        float GetAmbientIntensity() const { return ambientIntensity; }
        
        // GPU data management
        void UpdateLightingData();
        const LightingData& GetLightingData() const { return lightingData; }
        
        // Constant buffer management
        void CreateLightingConstantBuffer();
        void UpdateLightingConstantBuffer();
        MyConstantBufferPtr GetLightingConstantBuffer() const { return lightingConstantBuffer; }
        
        // Debug & utility
        void LogLightingSummary() const;
        void EnableAllLights();
        void DisableAllLights();

    private:
        //* ╔═════════════════╗
        //* ║ Member Variables ║
        //* ╚═════════════════╝
        std::vector<std::shared_ptr<MyLight>> lights;
        LightingData lightingData;
        MyConstantBufferPtr lightingConstantBuffer;
        
        // Ambient lighting
        MyVector3 ambientLight;
        float ambientIntensity;
        
        // Internal management
        bool needsUpdate;
        
        //* ╔═════════════════╗
        //* ║ Helper Functions ║
        //* ╚═════════════════╝
        void SortLightsByType();
        void PackLightingData();
        void ValidateLightCount();
    };

} // namespace DX3D
