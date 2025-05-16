
#pragma once
#include <Core/DX3DCommon.h>
#include <Core/MyBase.h>
#include <Graphics/GraphicsLogUtils.h>

#include <d3d11.h>
#include <wrl.h>

namespace DX3D {
	struct GraphicsResourceDesc {
		BaseDesc base;
		std::shared_ptr<const MyGraphicsDevice> graphicsDevice;
		ID3D11Device& device;
		IDXGIFactory& factory;
	};

	class MyGraphicsResource : public MyBase {
	public:
		explicit MyGraphicsResource(const GraphicsResourceDesc& desc) :
			MyBase(desc.base),
			m_graphicsDevice(desc.graphicsDevice),
			m_device(desc.device),
			m_factory(desc.factory) {
		}

	protected:
		std::shared_ptr<const MyGraphicsDevice> m_graphicsDevice;
		ID3D11Device& m_device;
		IDXGIFactory& m_factory;
	};
}