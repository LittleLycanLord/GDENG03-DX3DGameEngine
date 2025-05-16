#pragma once
#include <Core/MyBase.h>
#include <Core/DX3DCore.h> 

namespace DX3D {
	class MyGame : public MyBase {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		std::unique_ptr<MyLogger> m_loggerPtr{};
		std::unique_ptr<MyGraphicsEngine> m_graphicsEngine{};
		std::unique_ptr<MyDisplay> m_display{};
		bool m_isRunning{ true };
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyGame(const GameDesc& desc);
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


