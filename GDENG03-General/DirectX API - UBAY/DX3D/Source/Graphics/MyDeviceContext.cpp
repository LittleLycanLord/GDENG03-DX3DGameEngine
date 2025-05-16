

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

void DX3D::MyDeviceContext::setVertexBuffer(MyVertexBuffer* vertexBuffer) {
	UINT stride = vertexBuffer->size_vertex;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer->buffer, &stride, &offset);
	context->IASetInputLayout(vertexBuffer->layout);
}

void DX3D::MyDeviceContext::drawTriangleList(UINT vertexCount, UINT startIndex) {
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(vertexCount, startIndex);
}

void DX3D::MyDeviceContext::setViewport(UINT width, UINT height) {
	D3D11_VIEWPORT viewport{};
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝