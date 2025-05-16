

#pragma once
#include <Graphics/MyGraphicsResource.h>
#include <Math/MyVec4.h>

namespace DX3D {
	class MyDeviceContext final : public MyGraphicsResource {
	public:
		explicit MyDeviceContext(const GraphicsResourceDesc& gDesc);
		void clearAndSetBackBuffer(const MySwapChain& swapChain, const MyVec4& color);
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

		friend class MyGraphicsDevice;
	};
}

