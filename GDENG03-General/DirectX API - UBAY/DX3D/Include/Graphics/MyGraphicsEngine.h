#pragma once
#include <Core/DX3DCore.h>
#include <Core/DX3DCommon.h>
#include <Core/MyBase.h>
#include <Graphics/MyVertexBuffer.h>

namespace DX3D {
	class MyGraphicsEngine final : public MyBase {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		std::shared_ptr<MyGraphicsDevice> graphicsDevice{};
		DeviceContextPointer deviceContext{};
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyGraphicsEngine(const GraphicsEngineDescription& description);
		virtual ~MyGraphicsEngine() override;

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
	public:
		void render(MySwapChain& swapChain);
		MyVertexBuffer* createVertexBuffer();

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

