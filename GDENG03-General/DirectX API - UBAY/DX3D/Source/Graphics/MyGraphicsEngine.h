#pragma once
#include <Core/DX3DCore.h>
#include <Core/MyBase.h>

namespace DX3D {
	class MyGraphicsEngine final : public MyBase {
	public:
		explicit MyGraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~MyGraphicsEngine() override;

		MyGraphicsDevice& getGraphicsDevice() noexcept;

		void render(MySwapChain& swapChain);
	private:
		std::shared_ptr<MyGraphicsDevice> m_graphicsDevice{};
		DeviceContextPointer m_deviceContext{};
	};
}

