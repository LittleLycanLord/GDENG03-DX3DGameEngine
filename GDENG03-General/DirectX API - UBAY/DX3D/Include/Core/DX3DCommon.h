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

    struct DisplayDescription {
        WindowDescription window;
        MyGraphicsDevice& graphicsDevice;
    };

    struct GraphicsEngineDescription {
        BaseDescription base;
    };

    struct GraphicsDeviceDescription {
        BaseDescription base;
    };

    struct SwapChainDescription {
        void* windowHandle{};
        MyRectangle windowSize{};
    };


    struct GameDescription {
        MyRectangle windowSize{ 1280,720 };
        MyLogger::LogLevel logLevel = MyLogger::LogLevel::Error;
    };
}