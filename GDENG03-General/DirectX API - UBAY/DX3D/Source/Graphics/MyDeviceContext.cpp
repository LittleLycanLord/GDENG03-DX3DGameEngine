

#include <Graphics/MyDeviceContext.h>
#include <Graphics/MySwapChain.h>

DX3D::MyDeviceContext::MyDeviceContext(const GraphicsResourceDesc& gDesc) : MyGraphicsResource(gDesc) {
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDeferredContext failed.");
}

void DX3D::MyDeviceContext::clearAndSetBackBuffer(const MySwapChain& swapChain, const MyVec4& color) {
	float fColor[] = { color.x,color.y,color.z,color.w };
	auto rtv = swapChain.m_rtv.Get();
	m_context->ClearRenderTargetView(rtv, fColor);
	m_context->OMSetRenderTargets(1, &rtv, nullptr);
}
