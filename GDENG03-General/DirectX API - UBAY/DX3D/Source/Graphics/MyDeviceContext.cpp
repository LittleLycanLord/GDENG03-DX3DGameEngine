

#include <Graphics/MyDeviceContext.h>
#include <Graphics/MySwapChain.h>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyDeviceContext::MyDeviceContext(const GraphicsResourceDesc& gDesc) : MyGraphicsResource(gDesc) {
	DX3DGraphicsLogThrowOnFail(device.CreateDeferredContext(0, &context),
		"CreateDeferredContext failed.");
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MyDeviceContext::clearAndSetBackBuffer(const MySwapChain& swapChain, const MyVec4& color) {
	float fColor[] = { color.x,color.y,color.z,color.w };
	auto rtv = swapChain.rtv.Get();
	context->ClearRenderTargetView(rtv, fColor);
	context->OMSetRenderTargets(1, &rtv, nullptr);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝