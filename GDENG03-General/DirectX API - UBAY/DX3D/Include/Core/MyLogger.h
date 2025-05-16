#pragma once

namespace DX3D {
    class MyLogger final {
    public:
        enum class LogLevel {
            Error = 0,
            Warning,
            Info
        };
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        LogLevel logLevel = LogLevel::Error;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        explicit MyLogger(LogLevel logLevel = LogLevel::Error);
        ~MyLogger();

        MyLogger(const MyLogger&) = delete;
        MyLogger(MyLogger&&) = delete;
        MyLogger& operator = (const MyLogger&) = delete;
        MyLogger& operator=(MyLogger&&) = delete;
        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void log(LogLevel level, const char* message);

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


#define DX3DLogInfo(message)\
	getLogger().log((MyLogger::LogLevel::Info), message);

#define DX3DLogWarning(message)\
	getLogger().log((MyLogger::LogLevel::Warning), message);

#define DX3DLogError(message)\
	getLogger().log((MyLogger::LogLevel::Error), message);

#define DX3DLogErrorAndThrow(message)\
	{\
	DX3DLogError(message);\
	throw std::runtime_error(message);\
	}
} // namespace DX3D