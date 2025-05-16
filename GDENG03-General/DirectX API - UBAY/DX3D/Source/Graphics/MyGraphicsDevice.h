#pragma once
#include <Graphics/MyGraphicsResource.h>
#include <Core/DX3DCommon.h>
#include <Core/MyBase.h>
#include <d3d11.h>
#include <wrl.h>

namespace DX3D {
	class MyGraphicsDevice final : public MyBase, public std::enable_shared_from_this<MyGraphicsDevice> {
	public:
		explicit MyGraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~MyGraphicsDevice() override;

		SwapChainPointer createSwapChain(const SwapChainDesc& desc);
		DeviceContextPointer createDeviceContext();

		void executeCommandList(MyDeviceContext& context);
	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};
	};
}

