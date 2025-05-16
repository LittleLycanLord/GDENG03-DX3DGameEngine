#pragma once
#include <Core/DX3DCore.h>
#include <Core/MyBase.h>

namespace DX3D {
	class MyGraphicsEngine final : public MyBase {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		std::shared_ptr<MyGraphicsDevice> m_graphicsDevice{};
		DeviceContextPointer m_deviceContext{};
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyGraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~MyGraphicsEngine() override;

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
	public:
		void render(MySwapChain& swapChain);

		//* ╔════════════════════════════════╗
		//* ║ Virtual / Overridden Functions ║
		//* ╚════════════════════════════════╝
	protected:
	public:

		//* ╔═══════════════════╗
		//* ║ Getters & Setters ║
		//* ╚═══════════════════╝
	public:
		MyGraphicsDevice& getGraphicsDevice() noexcept;
	};
} // namespace DX3D

