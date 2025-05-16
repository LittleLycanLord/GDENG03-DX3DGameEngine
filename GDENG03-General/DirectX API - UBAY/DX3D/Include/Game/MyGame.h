#pragma once
#include <Core/MyBase.h>
#include <Core/DX3DCore.h> 
#include <Graphics/MyVertexBuffer.h> 

namespace DX3D {
	class MyGame : public MyBase {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		std::unique_ptr<MyLogger>loggerPtr{};
		std::unique_ptr<MyGraphicsEngine>graphicsEngine{};
		MyVertexBuffer* vertexBuffer{};
		std::unique_ptr<MyDisplay>display{};
		bool isRunning{ true };
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyGame(const GameDescription& description);
		virtual ~MyGame() override;

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
		void onInternalUpdate();
	public:
		virtual void run() final;

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