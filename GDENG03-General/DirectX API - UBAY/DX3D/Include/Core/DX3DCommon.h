#pragma once
#include <Core/DX3DCore.h>
#include <Core/MyLogger.h>
#include <Math/MyRect.h>

namespace DX3D {
    struct BaseDescription {
        MyLogger& logger;
    };

    struct WindowDescription {
        BaseDescription base;
        MyRectangle size{};
    };

    struct DisplayDesc {
        WindowDescription window;
        MyGraphicsDevice& graphicsDevice;
    };

    struct GraphicsEngineDesc {
        BaseDescription base;
    };

    struct GraphicsDeviceDesc {
        BaseDescription base;
    };

    struct SwapChainDesc {
        void* winHandle{};
        MyRectangle winSize{};
    };


    struct GameDesc {
        MyRectangle windowSize{ 1280,720 };
        MyLogger::LogLevel logLevel = MyLogger::LogLevel::Error;
    };
}