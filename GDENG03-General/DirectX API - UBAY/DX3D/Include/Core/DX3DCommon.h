#pragma once
#include <Core/DX3DCore.h>
#include <Core/MyLogger.h>
#include <Math/MyRect.h>

namespace DX3D {
    struct BaseDesc {
        MyLogger& logger;
    };

    struct WindowDesc {
        BaseDesc base;
        MyRect size{};
    };

    struct DisplayDesc {
        WindowDesc window;
        MyGraphicsDevice& graphicsDevice;
    };

    struct GraphicsEngineDesc {
        BaseDesc base;
    };

    struct GraphicsDeviceDesc {
        BaseDesc base;
    };

    struct SwapChainDesc {
        void* winHandle{};
        MyRect winSize{};
    };


    struct GameDesc {
        MyRect windowSize{ 1280,720 };
        MyLogger::LogLevel logLevel = MyLogger::LogLevel::Error;
    };
}