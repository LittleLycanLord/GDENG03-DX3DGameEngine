#include "Core/MyLogger.h"
#include <iostream>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyLogger::MyLogger(LogLevel logLevel) :logLevel(logLevel) {
    std::clog << "Conrad Ubay | GDENG03 - DirectX11 3D Game Engine" << "\n";
    std::clog << "--------------------------------------" << "\n";
}

DX3D::MyLogger::~MyLogger() {
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MyLogger::log(LogLevel level, const char* message) {
    auto logLevelToString = [](LogLevel level) {
        switch (level) {
        case LogLevel::Info: return "Info";
        case LogLevel::Warning: return "Warning";
        case LogLevel::Error: return "Error";
        default: return "Unknown";
        }
        };

    if (level >logLevel) return;
    std::clog << "[DX3D " << logLevelToString(level) << "]: " << message << "\n";
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
