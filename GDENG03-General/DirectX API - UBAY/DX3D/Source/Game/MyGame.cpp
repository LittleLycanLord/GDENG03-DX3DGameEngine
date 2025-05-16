#include <Game/MyGame.h>
#include <Window/MyWindow.h>
#include <Graphics/MyGraphicsEngine.h>
#include <Core/MyLogger.h>
#include <Game/MyDisplay.h>
#include <Math/MyVertex.h>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝

DX3D::MyGame::MyGame(const GameDescription& description) :
	MyBase({ *std::make_unique<MyLogger>(description.logLevel).release() }),
	loggerPtr(&logger) {
	graphicsEngine = std::make_unique<MyGraphicsEngine>(GraphicsEngineDescription{ logger });
	display = std::make_unique<MyDisplay>(DisplayDescription{ {logger,description.windowSize},graphicsEngine->getGraphicsDevice() });

	MyVertex vertices[] = {
		{ 0.0f, 0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f }
	};

	vertexBuffer = graphicsEngine->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);

	vertexBuffer->load(vertices, sizeof(MyVertex), size_list, nullptr, 0);
	DX3DLogInfo("MyGame initialized.");
}

DX3D::MyGame::~MyGame() {
	DX3DLogInfo("MyGame is shutting down...");
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MyGame::onInternalUpdate() {
	graphicsEngine->render(display->getSwapChain());
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝

